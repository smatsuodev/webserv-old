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
    // TODO: set header with ResponseWriter
}

void Context::text(HttpStatusCode status, const std::string &body) {
    // TODO: send text response with ResponseWriter
    // set Content-Type header to "text/plain"
}

void Context::html(HttpStatusCode status, const std::string &body) {
    // TODO: send html response with ResponseWriter
    // set Content-Type header to "text/html"
}

void Context::redirect(HttpStatusCode status, const std::string &location) {
    // TODO: send redirect response with ResponseWriter
    // set Location header
}

IOTaskManager &Context::getManager() const {
    return manager_;
}

int Context::getClientFd() const {
    return client_fd_;
}
