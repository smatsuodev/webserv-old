#include "context.hpp"

IContext::~IContext() {}

Context::Context(IOTaskManager &manager, int client_fd) : manager_(manager), client_fd_(client_fd) {}

const Request &Context::getRequest() const {
    return request_;
}

void Context::setRequest(const Request &request) {
    request_ = request;
}

void Context::setHeader(const std::string &name, const std::string &value) {
}

void Context::text(HttpStatusCode status, const std::string &body) {
}

void Context::html(HttpStatusCode status, const std::string &body) {
}

void Context::redirect(HttpStatusCode status, const std::string &location) {
}
