#include "read_request.hpp"
#include "http/request_parser.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

ReadRequest::ReadRequest(IContext *ctx, IReadRequestCallback *cb)
    : IOTask(ctx->getManager(), ctx->getClientFd()), ctx_(ctx), cb_(cb), reader_(ctx->getClientFd()) {}

ReadRequest::~ReadRequest() {
    delete cb_;
}

// HTTP-message = start-line CRLF *( field-line CRLF ) CRLF [ message-body ]
Result<IOTaskResult, std::string> ReadRequest::execute() {
    // start-line CRLF
    const Result<std::string, std::string> read_start_line_result = reader_.getline();
    if (read_start_line_result.isErr()) {
        return Err(read_start_line_result.unwrapErr());
    }
    std::string start_line = read_start_line_result.unwrap();
    if (!utils::endsWith(start_line, "\r\n")) {
        return Err<std::string>("start-line does not end with CRLF");
    }
    req_buffer_ << start_line;

    // *( field-line CRLF ) CRLF
    Option<size_t> content_length = None;
    while (true) {
        const Result<std::string, std::string> read_field_line_result = reader_.getline();
        if (read_field_line_result.isErr()) {
            return Err(read_field_line_result.unwrapErr());
        }
        const std::string &field_line = read_field_line_result.unwrap();
        if (!utils::endsWith(field_line, "\r\n")) {
            return Err<std::string>("field-line does not end with CRLF");
        }

        req_buffer_ << field_line;

        if (field_line == "\r\n") {
            break;
        }

        // Content-Length ヘッダーの値を取得
        // TODO: validation を適切に行う
        if (utils::startsWith(field_line, "Content-Length")) {
            // "Content-Length:" で 15 文字
            const std::string &content_length_str = field_line.substr(16);
            content_length = Some(std::stoul(content_length_str));
        }
    }

    if (content_length.isSome()) {
        // message-body
        const size_t &body_len = content_length.unwrap();
        const Result<std::string, std::string> read_request_body_result = reader_.read(body_len);
        if (read_request_body_result.isErr()) {
            return Err(read_request_body_result.unwrapErr());
        }
        const std::string &request_body = read_request_body_result.unwrap();
        req_buffer_ << request_body;
    }

    const std::string &raw_request = req_buffer_.str();
    Result<Request, std::string> parse_result = RequestParser::parseRequest(raw_request);
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
