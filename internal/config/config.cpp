#include "config.hpp"

Config::Config() : client_max_body_size_(kDefaultClientMaxBodySize) {
    ParseConfigFile(kDefaultPath);
    SetDefaultErrorPages();
}

Config::Config(const std::string &path) : client_max_body_size_(kDefaultClientMaxBodySize) {
    ParseConfigFile(path);
    SetDefaultErrorPages();
}

Config::Config(
        const std::vector<VirtualServerConfig> &virtual_servers,
        const std::map<HttpStatusCode, std::string> &error_pages,
        unsigned int client_max_body_size)
    : client_max_body_size_(client_max_body_size),
      virtual_servers_(virtual_servers),
      error_pages_(error_pages) {
    SetDefaultErrorPages();
}

Config::~Config() {}

Config::Config(const Config &other)
    : client_max_body_size_(other.client_max_body_size_),
      virtual_servers_(other.virtual_servers_),
      error_pages_(other.error_pages_) {}

Config &Config::operator=(const Config &other) {
    if (this != &other) {
        client_max_body_size_ = other.client_max_body_size_;
        virtual_servers_ = other.virtual_servers_;
        error_pages_ = other.error_pages_;
    }
    return *this;
}

void Config::ParseConfigFile(const std::string &path) {}

void Config::SetDefaultErrorPages() {}

/* getters */
unsigned int Config::GetClientMaxBodySize() const {
    return client_max_body_size_;
}

const std::vector<VirtualServerConfig> &Config::GetVirtualServers() const {
    return virtual_servers_;
}

const std::map<HttpStatusCode, std::string> &Config::GetErrorPages() const {
    return error_pages_;
}
