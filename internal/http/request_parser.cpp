#include "request_parser.hpp"

Request RequestParser::parseRequest(const std::string &raw_request) {
    return Request(kMethodUnknown, "/", std::map<std::string, std::string>(), std::map<std::string, std::string>(), raw_request);
}
