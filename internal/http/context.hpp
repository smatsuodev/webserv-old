#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "http/interface/context.hpp"
#include "request.hpp"
#include "response_writer.hpp"
#include "status.hpp"
#include "task/io_task_manager.hpp"

class Context : public IContext {
public:
    Context(IOTaskManager &manager, int client_fd);
    virtual const Request &getRequest() const;
    virtual void setRequest(const Request &request);
    virtual void setHeader(const std::string &name, const std::string &value);
    virtual void text(HttpStatusCode status, const std::string &body);
    virtual void html(HttpStatusCode status, const std::string &body);
    virtual void redirect(HttpStatusCode status, const std::string &location);
    virtual IOTaskManager &getManager() const;
    virtual int getClientFd() const;

private:
    IOTaskManager &manager_;
    Request request_;
    int client_fd_;
    ResponseWriter<int> writer_;
};

#endif //CONTEXT_HPP
