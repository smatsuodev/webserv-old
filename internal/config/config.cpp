#include "config.hpp"
#include "tokenizer.hpp"
#include "utils/result.hpp"
#include <fstream>

const std::string Config::kDefaultPath = "../conf/default.conf";

Config::Config() : client_max_body_size_(kDefaultClientMaxBodySize) {}

Config::Config(
        const std::vector<VirtualServerConfig> &virtual_servers,
        const std::map<HttpStatusCode, std::string> &error_pages,
        unsigned int client_max_body_size)
    : client_max_body_size_(client_max_body_size),
      virtual_servers_(virtual_servers),
      error_pages_(error_pages) {}

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

static bool cannotOpen(const std::string &path) {
    std::ifstream ifs(path);
    if (!ifs)
        return true;
    return false;
}

Result<Config, std::string> Config::parseConfigFile(const std::string &path) {
    Config config;
    if (cannotOpen(path))
        return Err<std::string>("Cannot open file");
    Tokenizer tokenizer(path);
    // TODO: ここで頑張ってパースする
    return Ok(config);
    //    return Err<std::string>("Not implemented");
}

// Set a default error page like nginx
// Do nothing if error page is already set
void Config::setDefaultErrorPage(HttpStatusCode code) {
    if (error_pages_.find(code) == error_pages_.end()) {
        error_pages_[code] = "";
    }
}

/* getters */
unsigned int Config::getClientMaxBodySize() const {
    return client_max_body_size_;
}

const std::vector<VirtualServerConfig> &Config::getVirtualServers() const {
    return virtual_servers_;
}

// If an error page is not set, generate a default one and store it to reduce resource usage
const std::string &Config::getErrorPage(HttpStatusCode code) {
    if (error_pages_.find(code) != error_pages_.end()) {
        return error_pages_.at(code);
    }
    setDefaultErrorPage(code);
    return error_pages_.at(code);
}
