#include "handler.hpp"
#include "task/write_file.hpp"

IHandler::~IHandler() {}

Result<types::Unit, std::string> Handler::trigger(std::string raw_request, int fd, IOTaskManager &manager) {
    new WriteFile(manager, fd, raw_request, new WriteFileCallback(fd));
    return Ok(unit);
}
