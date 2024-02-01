#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "http/status.hpp"
#include "utils/utils.hpp"
#include "virtual_server_config.hpp"
#include <map>
#include <string>

class Config {
public:
    Config();
    explicit Config(const std::string &path);
    ~Config();
    Config(const Config &other);
    Config &operator=(const Config &other);

    const std::string &GetConfigPath() const;
    unsigned int GetClientMaxBodySize() const;
    const std::vector<VirtualServerConfig> &GetVirtualServers() const;
    const std::map<HttpStatusCode, std::string> &GetErrorPages() const;

private:
    static const std::string kDefaultPath;
    // Same as nginx default
    // refs: https://nginx.org/en/docs/http/ngx_http_core_module.html#client_max_body_size
    static const unsigned int kDefaultClientMaxBodySize = utils::kMiB;

    // Path to config file to parse
    std::string config_path_;
    // Max body size of client request (bytes)
    unsigned int client_max_body_size_;
    // Config consists of virtual server configs
    std::vector<VirtualServerConfig> virtual_servers_;
    // Similar to error_page directive in nginx
    // Value is HTML of error page
    // refs: https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page
    std::map<HttpStatusCode, std::string> error_pages_;

    void ParseConfigFile(const std::string &path);
};

#endif //CONFIG_HPP
