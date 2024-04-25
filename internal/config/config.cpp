#include "config.hpp"
#include "tokenizer.hpp"
#include "utils/result.hpp"

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

static std::map<HttpStatusCode, std::string> parse_error_page(const std::string &block) {
    if (block.front() != '{' || block.back() != '}') {
        throw std::runtime_error("Invalid error_page directive");
    }
    std::string line = block.substr(1, block.size() - 2);
    line.erase(line.find_last_not_of(" \t") + 1);
    line.erase(0, line.find_first_not_of(" \t"));
    size_t pos = line.find('=');
    std::string key = "0";
    std::string value = "/";
    HttpStatusCode status = kStatusUnknown;
    if (pos != std::string::npos) {
        key = line.substr(0, pos);
        value = line.substr(pos + 1);
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
    } else {
        throw std::runtime_error("Invalid error_page directive");
    }
    char *end;
    status = httpStatusCodeFromInt((int)std::strtol(key.c_str(), &end, 10));
    if (*end != '\0' || errno == ERANGE || status == kStatusUnknown) {
        throw std::runtime_error("Invalid error_page directive");
    }
    std::map<HttpStatusCode, std::string> error_pages;
    error_pages[status] = value;
    return error_pages;
}

void    print_error_pages(const std::map<HttpStatusCode, std::string> &error_pages) {
    for (size_t k = 0; k < error_pages.size(); k++) {
        std::cout << "Error page: [" << error_pages.begin()->first << "] [" << error_pages.begin()->second << "]"<< std::endl;
    }
}

static std::map<HttpStatusCode, std::string> getErrorPages(const std::vector<std::pair<std::string, std::string> > &blocks) {
    std::map<HttpStatusCode, std::string> error_pages;
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].first == "error_page") {
            std::map<HttpStatusCode, std::string> parsed = parse_error_page(blocks[i].second);
            for (size_t j = 0; j < parsed.size(); j++) {
                if (error_pages.find(parsed.begin()->first) != error_pages.end()) {
                    throw std::runtime_error("Duplicate error_page directive");
                }
                error_pages[parsed.begin()->first] = parsed.begin()->second;
            }
        }
    }
    print_error_pages(error_pages);
    return error_pages;
}

Result<Config, std::string> Config::parseConfigFile(const std::string &path) {
    if (cannotOpen(path))
        return Err<std::string>("Cannot open file");
    Tokenizer tokenizer(path);
    std::map<HttpStatusCode, std::string> error_pages = getErrorPages(tokenizer.common_config_blocks_);
    Config config;
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
