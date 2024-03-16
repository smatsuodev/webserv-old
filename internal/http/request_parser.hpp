#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include "request.hpp"

class RequestParser {
public:
    static Request parseRequest(const std::string &raw_request);
};

#endif //REQUEST_PARSER_HPP
