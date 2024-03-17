#ifndef READREQUEST_HPP
#define READREQUEST_HPP

#include "handler/handler.hpp"
#include "io_task.hpp"
#include "utils/result.hpp"
#include "utils/unit.hpp"
#include "http/context.hpp"

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IReadRequestCallback {
public:
    virtual ~IReadRequestCallback();
    virtual Result<types::Unit, std::string> trigger(IContext *ctx) = 0;
};

class ReadRequestCallback : public IReadRequestCallback {
public:
    explicit ReadRequestCallback(IHandler *handler);
    virtual Result<types::Unit, std::string> trigger(IContext *ctx);

private:
    IHandler *handler_;
};

class ReadRequest : public IOTask {
public:
    ReadRequest(IContext *ctx, IReadRequestCallback *cb);
    ~ReadRequest();
    virtual Result<IOTaskResult, std::string> execute();

private:
    IContext *ctx_;
    IReadRequestCallback *cb_;
};

#endif
