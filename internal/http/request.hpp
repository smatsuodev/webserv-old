#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "method.hpp"
#include "utils/option.hpp"
#include <map>
#include <string>

class Request {
public:
    Request();
    Request(const std::string &raw_request);
    Request(const Request &request);
    ~Request();
    Request &operator=(const Request &other);
    HttpMethod method() const;
    const std::string &routePath() const;
    Option<std::string> query(const std::string &key) const;
    Option<std::string> header(const std::string &key) const;
    const std::string &text() const;

private:
    HttpMethod method_;
    std::string route_path_;
    std::map<std::string, std::string> queries_;
    std::map<std::string, std::string> headers_;
    std::string body_;

    void parseRawRequest(const std::string &raw_request);
};

#endif
