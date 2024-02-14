#ifndef CALLBACK_INTERFACE_HPP
#define CALLBACK_INTERFACE_HPP

#include "utils/unit.hpp"
#include <string>

template<typename T, typename E>
class Result;

class IAcceptCallback {
public:
    virtual Result<types::Unit, std::string> trigger(int client_fd) = 0;
};

class IReadRequestCallback {
public:
    virtual Result<types::Unit, std::string> trigger(std::string raw_request) = 0;
};

class IReadFileCallback {
public:
    virtual Result<types::Unit, std::string> trigger(std::string file_content) = 0;
};

class IWriteFileCallback {
public:
    virtual Result<types::Unit, std::string> trigger() = 0;
};

#endif //CALLBACK_INTERFACE_HPP
