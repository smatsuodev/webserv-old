#include "config/config.hpp"
#include "server/server.hpp"
#include <iostream>

int main(int argc, char **argv) {
    const std::string &path = (argc == 2) ? argv[1] : Config::kDefaultPath;
    Result<Config, std::string> parse_result = Config::parseConfigFile(path);
    if (parse_result.isErr()) {
        std::cerr << "Failed to parse config file: " << parse_result.unwrapErr() << std::endl;
        return 1;
    }
    Config config = parse_result.unwrap();
    Server server;

    Server::start();

    return 0;
}
