#include "handler.hpp"
#include "task/write_file.hpp"

IHandler::~IHandler() {}

Result<types::Unit, std::string> Handler::trigger(Context &ctx) {
    ctx.text(kStatusOk, ctx.getRequest().text());
    return Ok(unit);
}
