#include "config.hpp"

Config::Config() : client_max_body_size_(kDefaultClientMaxBodySize) {
    ParseConfigFile(kDefaultPath);
}

Config::Config(const std::string &path) : client_max_body_size_(kDefaultClientMaxBodySize) {
    ParseConfigFile(path);
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
