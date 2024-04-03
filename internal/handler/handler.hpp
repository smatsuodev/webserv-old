#ifndef INTERNAL_HANDLER_HANDLER_HPP
#define INTERNAL_HANDLER_HANDLER_HPP

#include "http/interface/context.hpp"
#include "task/io_task_manager.hpp"
#include "utils/result.hpp"
#include "utils/unit.hpp"
#include <string>

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IHandler {
public:
    virtual ~IHandler();
    virtual Result<types::Unit, std::string> trigger(IContext *ctx) = 0;
};

class Handler : public IHandler {
public:
    Result<types::Unit, std::string> trigger(IContext *ctx);
};
#endif //INTERNAL_HANDLER_HANDLER_HPP
