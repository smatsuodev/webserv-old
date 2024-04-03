#ifndef INTERNAL_CONFIG_VIRTUAL_SERVER_CONFIG_HPP
#define INTERNAL_CONFIG_VIRTUAL_SERVER_CONFIG_HPP

#include "route_config.hpp"
#include <string>
#include <vector>

class VirtualServerConfig {
public:
    VirtualServerConfig();
    explicit VirtualServerConfig(
            const std::vector<RouteConfig> &routes,
            const std::string &host = "0.0.0.0", const std::string &port = "80",
            const std::vector<std::string> &server_names = std::vector<std::string>());
    ~VirtualServerConfig();
    VirtualServerConfig(const VirtualServerConfig &other);
    VirtualServerConfig &operator=(const VirtualServerConfig &other);

    const std::string &getHost() const;
    const std::string &getPort() const;
    const std::vector<std::string> &getServerNames() const;
    const std::vector<RouteConfig> &getRoutes() const;

    static VirtualServerConfig parseVirtualServerConfigString(const std::string &config_string);

private:
    // Listen host
    std::string host_;
    // Listen port
    std::string port_;
    // A list of server names that the virtual server responds to
    std::vector<std::string> server_names_;
    // VirtualServerConfig consists of route configs
    std::vector<RouteConfig> routes_;
};

#endif //INTERNAL_CONFIG_VIRTUAL_SERVER_CONFIG_HPP
