#include "server/server.hpp"
#include "config/config.hpp"
#include <iostream>

int main(int argc, char **argv) {
    std::string path = (argc != 2) ? "default.conf" : argv[1];
    Config config = Config::parseConfigFile(path);
    Server server;

    Server::start();

    return 0;
}
