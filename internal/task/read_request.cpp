#include "read_request.hpp"
#include "http/request_parser.hpp"
#include <iostream>
#include <unistd.h>

ReadRequest::ReadRequest(IContext *ctx, IReadRequestCallback *cb)
    : IOTask(ctx->getManager(), ctx->getClientFd()), ctx_(ctx), cb_(cb) {}

ReadRequest::~ReadRequest() {
    delete cb_;
}

Result<IOTaskResult, std::string> ReadRequest::execute() {
    char buffer[1025];       // read の引数
    std::string raw_request; // callback に渡す文字列
    ssize_t read_len;
    while ((read_len = read(fd_, buffer, 1024)) != 0) {
        if (read_len == -1) break;
        buffer[read_len] = 0;
        raw_request.append(buffer);
    }

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
