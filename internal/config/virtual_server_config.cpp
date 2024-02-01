#include "virtual_server_config.hpp"

VirtualServerConfig::VirtualServerConfig() {}

VirtualServerConfig::VirtualServerConfig(const std::string &config_string) {
    ParseVirtualServerConfigString(config_string);
}

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

void VirtualServerConfig::ParseVirtualServerConfigString(const std::string &config_string) {}

/* getters */
const std::string &VirtualServerConfig::GetHost() const {
    return host_;
}

const std::string &VirtualServerConfig::GetPort() const {
    return port_;
}

const std::vector<std::string> &VirtualServerConfig::GetServerNames() const {
    return server_names_;
}

const std::vector<RouteConfig> &VirtualServerConfig::GetRoutes() const {
    return routes_;
}
