#include "handler.hpp"
#include "task/write_file.hpp"

IHandler::~IHandler() {}

Result<types::Unit, std::string> Handler::trigger(IContext *ctx) {
    const std::string data_to_write = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello";
    new WriteFile(ctx, data_to_write, new WriteFileCallback(ctx));
    return Ok(unit);
}
