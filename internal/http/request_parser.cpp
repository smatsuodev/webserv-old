#include "request_parser.hpp"

Result<Request, std::string>
RequestParser::parseRequest(const std::string &request_line, const std::vector<std::string> &headers, const Option<std::string> &body) {
    Request req = Request(kMethodUnknown, "/", std::map<std::string, std::string>(), std::map<std::string, std::string>(), "Hello");
    return Ok(req);
}
