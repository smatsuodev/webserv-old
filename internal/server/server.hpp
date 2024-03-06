#ifndef SERVER_HPP
#define SERVER_HPP

#include "utils/result.hpp"
#include "utils/unit.hpp"
#include <string>

class Server {
public:
    Server();
    Server(const Server &other);
    ~Server();
    Server &operator=(const Server &other);
    static Result<types::Unit, std::string> start(void);

private:
    static Result<int, std::string> createServerSocket();
};

#endif
