#ifndef ROUTE_CONFIG_HPP
#define ROUTE_CONFIG_HPP

#include "http/method.hpp"
#include <map>
#include <string>
#include <vector>

class RouteConfig {
public:
    RouteConfig();
    explicit RouteConfig(const std::string &config_string);
    explicit RouteConfig(
            const std::string &route_path,
            const std::vector<HttpMethod> &allowed_methods,
            const std::string &document_root = "/",
            const std::string &upload_path = "/tmp",
            const std::string &redirect_path = "/",
            bool autoindex_enabled = false,
            const std::string &index_file_name = "index.html",
            const std::vector<std::string> &cgi_extensions = std::vector<std::string>(),
            const std::map<std::string, std::string> &response_headers = std::map<std::string, std::string>());
    ~RouteConfig();
    RouteConfig(const RouteConfig &other);
    RouteConfig &operator=(const RouteConfig &other);

    const std::string &getRoutePath() const;
    const std::vector<HttpMethod> &getAllowedMethods() const;
    const std::string &getUploadPath() const;
    const std::string &getDocumentRoot() const;
    bool isAutoindexEnabled() const;
    const std::string &getIndexFileName() const;
    const std::string &getRedirectPath() const;
    const std::vector<std::string> &getCgiExtensions() const;
    const std::map<std::string, std::string> &getResponseHeaders() const;

private:
    // Path for the route, similar to location directive in nginx
    // refs: https://nginx.org/en/docs/http/ngx_http_core_module.html#location
    std::string route_path_;
    // Allowed HTTP methods
    // Request with method not in this list will be rejected
    std::vector<HttpMethod> allowed_methods_;
    // Path to save uploaded files
    std::string upload_path_;
    // Root directory for serving files, similar to root directive in nginx
    // refs: https://nginx.org/en/docs/http/ngx_http_core_module.html#root
    std::string document_root_;
    // Whether to enable autoindex, similar to autoindex directive in nginx
    // refs: https://nginx.org/en/docs/http/ngx_http_autoindex_module.html
    bool autoindex_enabled_;
    // Index file name, similar to index directive in nginx
    // refs: https://nginx.org/en/docs/http/ngx_http_index_module.html#index
    std::string index_file_name_;
    // Server responds with 302 Found and Location header set to this value
    std::string redirect_path_;
    // Extensions of CGI scripts
    std::vector<std::string> cgi_extensions_;
    // Server responds by appending these headers
    std::map<std::string, std::string> response_headers_;

    void parseRouteConfigString(const std::string &config_string);
};

#endif //ROUTE_CONFIG_HPP
