#ifndef INTERNAL_HTTP_INTERFACE_CONTEXT_HPP
#define INTERNAL_HTTP_INTERFACE_CONTEXT_HPP

#include "http/request.hpp"
#include "http/status.hpp"
#include "task/io_task_manager.hpp"

class IContext {
public:
    virtual ~IContext();
    virtual const Request &getRequest() const = 0;
    virtual void setRequest(const Request &request) = 0;
    virtual void setHeader(const std::string &name, const std::string &value) = 0;
    virtual void text(HttpStatusCode status, const std::string &body) = 0;
    virtual void html(HttpStatusCode status, const std::string &body) = 0;
    virtual void redirect(HttpStatusCode status, const std::string &location) = 0;
    virtual IOTaskManager &getManager() const = 0;
    virtual int getClientFd() const = 0;
};

#endif //INTERNAL_HTTP_INTERFACE_CONTEXT_HPP
