#include "request_parser.hpp"

Result<Request, std::string> RequestParser::parseRequest(const std::string &raw_request) {
    Request req = Request(kMethodUnknown, "/", std::map<std::string, std::string>(), std::map<std::string, std::string>(), raw_request);
    return Ok(req);
}
