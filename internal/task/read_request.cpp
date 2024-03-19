#include "read_request.hpp"
#include "http/request_parser.hpp"
#include <iostream>

ReadRequest::ReadRequest(IContext *ctx, IReadRequestCallback *cb)
    : IOTask(ctx->getManager(), ctx->getClientFd()), ctx_(ctx), cb_(cb), reader_(ctx->getClientFd()) {}

ReadRequest::~ReadRequest() {
    delete cb_;
}

// TODO: ノンブロッキング対応
// TODO: 400 Bad Request を返す
// HTTP-request = request-line CRLF *( field-line CRLF ) CRLF [ message-body ]
Result<IOTaskResult, std::string> ReadRequest::execute() {
    // request-line CRLF
    const Result<std::string, std::string> read_request_line_result = reader_.getline();
    if (read_request_line_result.isErr()) {
        return Err(read_request_line_result.unwrapErr());
    }
    std::string request_line = read_request_line_result.unwrap();
    if (!utils::endsWith(request_line, "\r\n")) {
        return Err<std::string>("start-line does not end with CRLF");
    }

    request_line.erase(request_line.size() - 2); // remove CRLF

    // *( field-line CRLF ) CRLF
    Option<size_t> content_length = None;
    while (true) {
        const Result<std::string, std::string> read_header_result = reader_.getline();
        if (read_header_result.isErr()) {
            return Err(read_header_result.unwrapErr());
        }
        std::string header = read_header_result.unwrap();
        if (!utils::endsWith(header, "\r\n")) {
            return Err<std::string>("field-line does not end with CRLF");
        }

        if (header == "\r\n") {
            break;
        }

        header.erase(header.size() - 2); // remove CRLF
        headers_.push_back(header);

        // Content-Length ヘッダーの値を取得
        Result<std::pair<std::string, std::string>, std::string> parse_field_result = RequestParser::parseHeaderFieldLine(header);
        if (parse_field_result.isErr()) {
            return Err(parse_field_result.unwrapErr());
        }
        const std::pair<std::string, std::string> &field = parse_field_result.unwrap();
        if (field.first == "Content-Length") {
            // TODO: std::stoul を使わない
            content_length = Some(std::stoul(field.second));
        }
    }

    Option<std::string> maybe_body = None;
    if (content_length.isSome()) {
        // message-body
        const size_t &body_size = content_length.unwrap();
        const Result<std::string, std::string> read_body_result = reader_.read(body_size);
        if (read_body_result.isErr()) {
            return Err(read_body_result.unwrapErr());
        }
        maybe_body = Some(read_body_result.unwrap());
    }

    Result<Request, std::string> parse_result = RequestParser::parseRequest(request_line, headers_, maybe_body.unwrapOr(""));
    if (parse_result.isErr()) {
        return Err(parse_result.unwrapErr());
    }
    ctx_->setRequest(parse_result.unwrap());
    cb_->trigger(ctx_);
    return Ok(kTaskComplete);
}

IReadRequestCallback::~IReadRequestCallback() {}

ReadRequestCallback::ReadRequestCallback(IHandler *handler) : handler_(handler) {}

Result<types::Unit, std::string> ReadRequestCallback::trigger(IContext *ctx) {
    handler_->trigger(ctx);
    return Ok(unit);
}
