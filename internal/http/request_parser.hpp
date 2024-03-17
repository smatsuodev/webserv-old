#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "request.hpp"
#include "utils/result.hpp"

class RequestParser {
public:
    Result<Request, std::string> parseRequest(const std::string &request_line, const std::vector<std::string> &headers, const Option<std::string> &body);
    static Result<std::pair<std::string, std::string>, std::string> parseHeaderFieldLine(const std::string &line);

private:
};

#endif //REQUEST_PARSER_HPP
