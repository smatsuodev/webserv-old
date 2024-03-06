#ifndef READREQUEST_HPP
#define READREQUEST_HPP

#include "handler/handler.hpp"
#include "io_task.hpp"
#include "utils/result.hpp"
#include "utils/unit.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IReadRequestCallback {
public:
    virtual ~IReadRequestCallback();
    virtual Result<types::Unit, std::string> trigger(std::string raw_request, IOTaskManager &manager, int fd) = 0;
};

class ReadRequestCallback : public IReadRequestCallback {
public:
    ReadRequestCallback(IHandler *handler);
    virtual Result<types::Unit, std::string> trigger(std::string raw_request, IOTaskManager &manager, int fd);

private:
    IHandler *handler_;
};

class ReadRequest : public IOTask {
public:
    ReadRequest(IOTaskManager &manager, int client_fd, IReadRequestCallback *cb);
    ~ReadRequest();
    virtual Result<IOTaskResult, std::string> execute();

private:
    IReadRequestCallback *cb_;
};

#endif
