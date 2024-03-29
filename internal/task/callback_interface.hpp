#ifndef INTERNAL_TASK_CALLBACK_INTERFACE_HPP
#define INTERNAL_TASK_CALLBACK_INTERFACE_HPP

#include "utils/unit.hpp"
#include <string>

template<typename T, typename E>
class Result;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IReadFileCallback {
public:
    virtual ~IReadFileCallback() = 0;
    virtual Result<types::Unit, std::string> trigger(std::string file_content) = 0;
};

#endif //INTERNAL_TASK_CALLBACK_INTERFACE_HPP
