#include "config.hpp"

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

Config Config::parseConfigFile(const std::string &path) {
    (void) path;
    return Config();
}

// Set a default error page like nginx
// Do nothing if error page is already set
void Config::setDefaultErrorPage(const HttpStatusCode code) {
    if (error_pages_.find(code) == error_pages_.end()) {
        const std::string text = utils::toString(code) + " " + getHttpStatusText(code);
        error_pages_[code] =
                "<html>"
                "<head><title>" + text + "</title></head>"
                "<body>"
                "<center><h1>" + text + "</h1></center>"
                "<hr>"
                "<center>webserv/0.1.0</center>"
                "</body>"
                "</html>";
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
const std::string &Config::getErrorPage(const HttpStatusCode code) {
    if (error_pages_.find(code) != error_pages_.end()) {
        return error_pages_.at(code);
    }
    setDefaultErrorPage(code);
    return error_pages_.at(code);
}
