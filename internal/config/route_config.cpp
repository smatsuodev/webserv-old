#include "route_config.hpp"

RouteConfig::RouteConfig() : autoindex_enabled_() {}

RouteConfig::RouteConfig(const std::string &config_string) : autoindex_enabled_() {
    ParseRouteConfigString(config_string);
}

RouteConfig::RouteConfig(
        const std::string &route_path,
        const std::vector<HttpMethod> &allowed_methods,
        const std::string &document_root,
        const std::string &upload_path,
        const std::string &redirect_path,
        bool autoindex_enabled,
        const std::string &index_file_name,
        const std::vector<std::string> &cgi_extensions,
        const std::map<std::string, std::string> &response_headers)
    : route_path_(route_path),
      allowed_methods_(allowed_methods),
      upload_path_(upload_path),
      document_root_(document_root),
      autoindex_enabled_(autoindex_enabled),
      index_file_name_(index_file_name),
      redirect_path_(redirect_path),
      cgi_extensions_(cgi_extensions),
      response_headers_(response_headers) {}

RouteConfig::~RouteConfig() {}

RouteConfig::RouteConfig(const RouteConfig &other)
    : route_path_(other.route_path_),
      allowed_methods_(other.allowed_methods_),
      upload_path_(other.upload_path_),
      document_root_(other.document_root_),
      autoindex_enabled_(other.autoindex_enabled_),
      index_file_name_(other.index_file_name_),
      redirect_path_(other.redirect_path_),
      cgi_extensions_(other.cgi_extensions_),
      response_headers_(other.response_headers_) {}

RouteConfig &RouteConfig::operator=(const RouteConfig &other) {
    if (this != &other) {
        route_path_ = other.route_path_;
        allowed_methods_ = other.allowed_methods_;
        upload_path_ = other.upload_path_;
        document_root_ = other.document_root_;
        autoindex_enabled_ = other.autoindex_enabled_;
        index_file_name_ = other.index_file_name_;
        redirect_path_ = other.redirect_path_;
        cgi_extensions_ = other.cgi_extensions_;
        response_headers_ = other.response_headers_;
    }
    return *this;
}

void RouteConfig::ParseRouteConfigString(const std::string &config_string) {}

/* getters */
const std::string &RouteConfig::GetRoutePath() const {
    return route_path_;
}

const std::vector<HttpMethod> &RouteConfig::GetAllowedMethods() const {
    return allowed_methods_;
}

const std::string &RouteConfig::GetUploadPath() const {
    return upload_path_;
}

const std::string &RouteConfig::GetDocumentRoot() const {
    return document_root_;
}

bool RouteConfig::IsAutoindexEnabled() const {
    return autoindex_enabled_;
}

const std::string &RouteConfig::GetIndexFileName() const {
    return index_file_name_;
}

const std::string &RouteConfig::GetRedirectPath() const {
    return redirect_path_;
}

const std::vector<std::string> &RouteConfig::GetCgiExtensions() const {
    return cgi_extensions_;
}

const std::vector<std::pair<std::string, std::string> > &RouteConfig::GetResponseHeaders() const {
    return response_headers_;
}
