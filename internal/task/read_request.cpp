#include "read_request.hpp"
#include <iostream>
#include <unistd.h>

ReadRequest::ReadRequest(IOTaskManager &manager, int client_fd, IReadRequestCallback *cb)
    : IOTask(manager, client_fd), cb_(cb) {}

ReadRequest::~ReadRequest() {
    delete cb_;
}

Result<IOTaskResult, std::string> ReadRequest::execute() {
    char buffer[1025] = {};  // read の引数
    std::string raw_request; // callback に渡す文字列
    ssize_t read_len = 0;
    while ((read_len = read(fd_, buffer, 1024)) != 0) {
        if (read_len == -1) break;
        raw_request.append(buffer);
    }
    cb_->trigger(raw_request, manager_, fd_);
    return Ok(kTaskComplete);
}

IReadRequestCallback::~IReadRequestCallback() {}

ReadRequestCallback::ReadRequestCallback(IHandler *handler) : handler_(handler) {}

// FIXME: 本当はContextが欲しい
Result<types::Unit, std::string> ReadRequestCallback::trigger(std::string raw_request, IOTaskManager &manager, int fd) {
    handler_->trigger(raw_request, fd, manager);
    return Ok(unit);
}
