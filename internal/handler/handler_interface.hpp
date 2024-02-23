#ifndef HANDLER_INTERFACE_HPP
#define HANDLER_INTERFACE_HPP

#include "utils/unit.hpp"
#include <string>

template<typename T, typename E>
class Result;

class Context;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IHandler {
public:
    virtual ~IHandler() = 0;
    virtual Result<types::Unit, std::string> trigger(Context &ctx) = 0;
};

#endif //HANDLER_INTERFACE_HPP
