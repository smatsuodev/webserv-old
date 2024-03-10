#ifndef ACCEPT_HPP
#define ACCEPT_HPP

#include "handler/handler.hpp"
#include "io_task.hpp"
#include "io_task_manager.hpp"
#include "utils/result.hpp"
#include "utils/unit.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IAcceptCallback {
public:
    virtual ~IAcceptCallback();
    virtual Result<types::Unit, std::string> trigger(int client_fd) = 0;
};

class AcceptCallback : public IAcceptCallback {
public:
    AcceptCallback(IOTaskManager &manager, IHandler *handler);
    virtual Result<types::Unit, std::string> trigger(int client_fd);

private:
    IOTaskManager &manager_; // NOLINT(*-avoid-const-or-ref-data-members)
    IHandler *handler_;
};

class Accept : public IOTask {
public:
    Accept(IOTaskManager &m, int fd, IAcceptCallback *cb);
    ~Accept();
    virtual Result<IOTaskResult, std::string> execute();

private:
    IAcceptCallback *cb_;
};

#endif
