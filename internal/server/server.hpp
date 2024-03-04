#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include "utils/result.hpp"
#include "utils/unit.hpp"

class Server {
public:
    Server();
    Server(const Server &other);
    ~Server();
    Server &operator=(const Server &other);
    Result<types::Unit, std::string>start(void);

private:
    Result<int, std::string> createServerSocket();
};

#endif
