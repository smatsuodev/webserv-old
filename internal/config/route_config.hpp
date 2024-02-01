#ifndef ROUTE_CONFIG_HPP
#define ROUTE_CONFIG_HPP

#include "http/method.hpp"
#include <string>
#include <vector>

class RouteConfig {
public:
    RouteConfig();
    explicit RouteConfig(const std::string &config_string);
    ~RouteConfig();
    RouteConfig(const RouteConfig &other);
    RouteConfig &operator=(const RouteConfig &other);

    const std::string &GetRoutePath() const;
    const std::vector<HttpMethod> &GetAllowedMethods() const;
    const std::string &GetUploadPath() const;
    const std::string &GetDocumentRoot() const;
    bool IsAutoindexEnabled() const;
    const std::string &GetIndexFileName() const;
    const std::string &GetRedirectPath() const;
    const std::vector<std::string> &GetCgiExtensions() const;
    const std::vector<std::pair<std::string, std::string> > &GetResponseHeaders() const;

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
    std::vector<std::pair<std::string, std::string> > response_headers_;

    void ParseRouteConfigString(const std::string &config_string);
};

#endif //ROUTE_CONFIG_HPP
