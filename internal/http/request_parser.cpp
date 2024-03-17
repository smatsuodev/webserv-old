#include "request_parser.hpp"

Result<Request, std::string>
RequestParser::parseRequest(const std::string &request_line, const std::vector<std::string> &headers, const Option<std::string> &body) {
    Request req = Request(kMethodUnknown, "/", std::map<std::string, std::string>(), std::map<std::string, std::string>(), "Hello");
    return Ok(req);
}

Result<std::pair<std::string, std::string>, std::string>
RequestParser::parseHeaderFieldLine(const std::string &line) {
    // TODO: 厳密にパースする
    const size_t pos = line.find(':');
    if (pos == std::string::npos) {
        return Err<std::string>("field-line does not contain ':'");
    }
    const std::string key = line.substr(0, pos);
    const std::string value = line.substr(pos + 1);
    return Ok(std::make_pair(key, value));
}