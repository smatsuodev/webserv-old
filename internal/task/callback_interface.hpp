#ifndef CALLBACK_INTERFACE_HPP
#define CALLBACK_INTERFACE_HPP

#include <string>

class IAcceptCallback {
public:
    virtual void trigger(int client_fd) = 0;
};

class IReadRequestCallback {
public:
    virtual void trigger(std::string raw_request) = 0;
};

class IReadFileCallback {
public:
    virtual void trigger(std::string file_content) = 0;
};

class IWriteFileCallback {
public:
   virtual void trigger() = 0;
};

#endif //CALLBACK_INTERFACE_HPP
