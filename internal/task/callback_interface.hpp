#ifndef CALLBACK_INTERFACE_HPP
#define CALLBACK_INTERFACE_HPP

#include "utils/unit.hpp"
#include <string>

template<typename T, typename E>
class Result;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IAcceptCallback {
public:
    virtual ~IAcceptCallback() = 0;
    virtual Result<types::Unit, std::string> trigger(int client_fd) = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IReadRequestCallback {
public:
    virtual ~IReadRequestCallback() = 0;
    virtual Result<types::Unit, std::string> trigger(std::string raw_request) = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IReadFileCallback {
public:
    virtual ~IReadFileCallback() = 0;
    virtual Result<types::Unit, std::string> trigger(std::string file_content) = 0;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IWriteFileCallback {
public:
    virtual ~IWriteFileCallback() = 0;
    virtual Result<types::Unit, std::string> trigger() = 0;
};

#endif //CALLBACK_INTERFACE_HPP
