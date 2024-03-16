#include "context.hpp"

IContext::~IContext() {}

Context::Context(IOTaskManager &manager, int client_fd)
    : manager_(manager), client_fd_(client_fd), writer_(manager, client_fd) {}

const Request &Context::getRequest() const {
    return request_;
}

void Context::setRequest(const Request &request) {
    request_ = request;
}

void Context::setHeader(const std::string &name, const std::string &value) {
    writer_.writeHeader(name, value);
}

void Context::text(HttpStatusCode status, const std::string &body) {
    writer_.setStatus(status);
    writer_.writeHeader("Content-Type", "text/plain");
    writer_.writeBody(body);
    writer_.send();
}

void Context::html(HttpStatusCode status, const std::string &body) {
    writer_.setStatus(status);
    writer_.writeHeader("Content-Type", "text/html");
    writer_.writeBody(body);
    writer_.send();
}

void Context::redirect(HttpStatusCode status, const std::string &location) {
    writer_.setStatus(status);
    writer_.writeHeader("Location", location);
    writer_.send();
}
