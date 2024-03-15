#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "http/context.hpp"
#include "task/io_task_manager.hpp"
#include "utils/result.hpp"
#include "utils/unit.hpp"
#include <string>

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IHandler {
public:
    virtual ~IHandler();
    virtual Result<types::Unit, std::string> trigger(Context &ctx) = 0;
};

class Handler : public IHandler {
public:
    Result<types::Unit, std::string> trigger(Context &ctx);
};
#endif //HANDLER_HPP
