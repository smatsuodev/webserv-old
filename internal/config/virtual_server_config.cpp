#include "virtual_server_config.hpp"

VirtualServerConfig::VirtualServerConfig() {}

VirtualServerConfig::VirtualServerConfig(
        const std::vector<RouteConfig> &routes,
        const std::string &host, const std::string &port,
        const std::vector<std::string> &server_names)
    : host_(host), port_(port), server_names_(server_names), routes_(routes) {}

VirtualServerConfig::~VirtualServerConfig() {}

VirtualServerConfig::VirtualServerConfig(const VirtualServerConfig &other)
    : host_(other.host_), port_(other.port_), server_names_(other.server_names_), routes_(other.routes_) {}

VirtualServerConfig &VirtualServerConfig::operator=(const VirtualServerConfig &other) {
    if (this != &other) {
        host_ = other.host_;
        port_ = other.port_;
        server_names_ = other.server_names_;
        routes_ = other.routes_;
    }
    return *this;
}

VirtualServerConfig VirtualServerConfig::parseVirtualServerConfigString(const std::string &config_string) {
    (void)config_string;
    return VirtualServerConfig();
}

/* getters */
const std::string &VirtualServerConfig::getHost() const {
    return host_;
}

const std::string &VirtualServerConfig::getPort() const {
    return port_;
}

const std::vector<std::string> &VirtualServerConfig::getServerNames() const {
    return server_names_;
}

const std::vector<RouteConfig> &VirtualServerConfig::getRoutes() const {
    return routes_;
}
