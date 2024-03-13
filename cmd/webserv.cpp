#include "config/config.hpp"
#include "server/server.hpp"
#include <iostream>
#define DEFAULT_CONFIG_PATH "default.conf"

int main(int argc, char **argv) {
    std::string path = (argc != 2) ? DEFAULT_CONFIG_PATH : argv[1];
    Result<Config, std::string> parse_result = Config::parseConfigFile(path);
    if (parse_result.isErr()) {
        std::cerr << "Failed to parse config file: " << parse_result.unwrapErr() << std::endl;
        return 1;
    }
    const Config &config = parse_result.unwrap();
    Server server;

    Server::start();

    return 0;
}
