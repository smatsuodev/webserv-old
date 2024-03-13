#include "request.hpp"

Request Request::parseRawRequest(const std::string &raw_request) {
    // TODO: パースの処理をかく
    return Request(
            kMethodUnknown,
            "/",
            std::map<std::string, std::string>(),
            std::map<std::string, std::string>(),
            raw_request);
}