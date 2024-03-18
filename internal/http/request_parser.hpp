#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "request.hpp"
#include "utils/result.hpp"

class RequestParser {
public:
    typedef std::pair<std::string, std::string> HeaderField;

    static Result<Request, std::string> parseRequest(const std::string &request_line, const std::vector<std::string> &headers, const Option<std::string> &body);
    static Result<std::pair<std::string, std::string>, std::string> parseHeaderFieldLine(const std::string &line);

private:
    // method, request-target, HTTP-version
    typedef std::pair<std::pair<HttpMethod, std::string>, std::string> RequestLine;

    static Result<RequestLine, std::string> parseRequestLine(const std::string &line);
};

#endif //REQUEST_PARSER_HPP
