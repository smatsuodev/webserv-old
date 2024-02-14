#ifndef HANDLER_INTERFACE_HPP
#define HANDLER_INTERFACE_HPP

#include "utils/unit.hpp"
#include <string>

template<typename T, typename E>
class Result;

class Context;

class IHandler {
public:
    virtual Result<types::Unit, std::string> trigger(Context &ctx) = 0;
};

#endif //HANDLER_INTERFACE_HPP
