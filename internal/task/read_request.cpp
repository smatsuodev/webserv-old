#include "read_request.hpp"
#include "http/request_parser.hpp"
#include <iostream>

ReadRequest::ReadRequest(IContext *ctx, IReadRequestCallback *cb, IBufferedReader *reader)
    : IOTask(ctx->getManager(), ctx->getClientFd()), ctx_(ctx), cb_(cb), reader_(reader) {}

ReadRequest::~ReadRequest() {
    delete cb_;
}

// TODO: ノンブロッキング対応
// TODO: 400 Bad Request を返す
// HTTP-request = request-line CRLF *( field-line CRLF ) CRLF [ message-body ]
Result<IOTaskResult, std::string> ReadRequest::execute() {
    // request-line CRLF
    std::string request_line = TRY(reader_->readLine("\r\n"));
    if (!utils::endsWith(request_line, "\r\n")) {
        return Err<std::string>("start-line does not end with CRLF");
    }

    request_line.erase(request_line.size() - 2); // remove CRLF

    // *( field-line CRLF ) CRLF
    Option<size_t> content_length = None;
    while (true) {
        std::string header = TRY(reader_->readLine("\r\n"));
        if (!utils::endsWith(header, "\r\n")) {
            return Err<std::string>("field-line does not end with CRLF");
        }

        if (header == "\r\n") {
            break;
        }

        header.erase(header.size() - 2); // remove CRLF
        headers_.push_back(header);

        // Content-Length ヘッダーの値を取得
        const std::pair<std::string, std::string> &field = TRY(RequestParser::parseHeaderFieldLine(header));
        if (field.first == "Content-Length") {
            // TODO: client_max_body_size より大きい値の場合はエラー
            content_length = Some(TRY(utils::stoul(field.second)));
        }
    }

    Option<std::string> maybe_body = None;
    if (content_length.isSome()) {
        // message-body
        const size_t &body_size = content_length.unwrap();
        char *buf = new char[body_size];
        TRY(reader_->read(buf, body_size));
        maybe_body = Some(std::string(buf, body_size));
        delete[] buf;
    }

    Request parsed_request = TRY(RequestParser::parseRequest(request_line, headers_, maybe_body.unwrapOr("")));
    ctx_->setRequest(parsed_request);
    if (cb_ != NULL)
        cb_->trigger(ctx_);
    return Ok(kTaskComplete);
}

IReadRequestCallback::~IReadRequestCallback() {}

ReadRequestCallback::ReadRequestCallback(IHandler *handler) : handler_(handler) {}

Result<types::Unit, std::string> ReadRequestCallback::trigger(IContext *ctx) {
    handler_->trigger(ctx);
    return Ok(unit);
}
