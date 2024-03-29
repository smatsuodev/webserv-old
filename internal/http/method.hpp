#ifndef INTERNAL_HTTP_METHOD_HPP
#define INTERNAL_HTTP_METHOD_HPP

#include <string>

enum HttpMethod {
    kMethodUnknown,
    kMethodGet,
    kMethodPost,
    kMethodPut,
    kMethodDelete,
    kMethodHead,
    kMethodOptions,
    kMethodTrace,
    kMethodConnect,
    kMethodPatch,
};

HttpMethod httpMethodFromString(const std::string &method);

#endif //INTERNAL_HTTP_METHOD_HPP
