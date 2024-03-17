#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "request.hpp"
#include "utils/result.hpp"

class RequestParser {
public:
    static Result<Request, std::string> parseRequest(const std::string &raw_request);
};

#endif //REQUEST_PARSER_HPP
