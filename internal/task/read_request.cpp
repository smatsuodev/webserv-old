#include "read_request.hpp"
#include "http/request_parser.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>

ReadRequest::ReadRequest(IContext *ctx, IReadRequestCallback *cb)
    : IOTask(ctx->getManager(), ctx->getClientFd()), ctx_(ctx), cb_(cb) {
    int fd_copy = dup(fd_);
    if (fd_copy == -1) {
        // TODO: handle error
    }
    stream_ = fdopen(fd_copy, "rb");
    if (stream_ == NULL) {
        // TODO: handle error
    }
}

ReadRequest::~ReadRequest() {
    delete cb_;
    std::fclose(stream_);
}

// HTTP-message = start-line CRLF *( field-line CRLF ) CRLF [ message-body ]
Result<IOTaskResult, std::string> ReadRequest::execute() {
    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_len = 0;

    // start-line CRLF
    line_len = getdelim(&line, &line_capacity, '\n', stream_);
    if (line_len == -1) {
        // エラーまたは EOF の場合
        // TODO: EOF の扱いを考える
        return Err<std::string>("failed to read request-line");
    }
    // TODO: 末尾が \r\n であることを確認する
    req_buffer_ << line;
    std::free(line);
    line = NULL;

    // *( field-line CRLF ) CRLF
    Option<size_t> content_length = None;
    while (true) {
        line_len = getdelim(&line, &line_capacity, '\n', stream_);
        if (line_len == -1) {
            // TODO: EOF の扱いを考える
            return Err<std::string>("failed to read field-line");
        }

        // TODO: 末尾が \r\n であることを確認する
        req_buffer_ << line;

        if (std::strcmp(line, "\r\n") == 0) {
            break;
        }

        // Content-Length ヘッダーの値を取得
        // TODO: validation を適切に行う
        if (std::strncmp(line, "Content-Length", 14) == 0) {
            const char *colon = std::strchr(line, ':');
            if (colon == NULL) {
                return Err<std::string>("failed to parse Content-Length");
            }
            const char *value = colon + 1;
            while (std::isspace(*value)) {
                value++;
            }
            content_length = Some(std::strtoul(value, NULL, 10));
        }

        std::free(line);
        line = NULL;
    }

    if (content_length.isSome()) {
        // message-body
        const size_t &body_len = content_length.unwrap();
        const size_t buffer_size = utils::kKiB;
        char body_buffer[std::min(body_len + 1, buffer_size)];
        size_t total_bytes_read = 0;
        // TODO: body が送られない場合のタイムアウト
        while (true) {
            const size_t &remaining_body_len = body_len - total_bytes_read;
            if (remaining_body_len == 0) {
                break;
            }

            const size_t bytes_read = std::fread(body_buffer, sizeof(char), std::min(remaining_body_len, buffer_size - 1), stream_);
            if (bytes_read == 0) {
                // エラーまたは EOF の場合
                // EOF なら body が足りない
                return Err<std::string>("failed to read request-body");
            }
            total_bytes_read += bytes_read;

            body_buffer[bytes_read] = '\0';
            req_buffer_ << body_buffer;
        }
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
