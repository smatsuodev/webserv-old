#include "accept.hpp"
#include "utils/result.hpp"
#include <iostream>

Accept::Accept(IOTaskManager &m, int fd) : IOTask(m, fd) {}

Accept::~Accept() {
}

Result<IOTaskResult, std::string> Accept::execute() {
    std::cout << "Accept::execute()" << std::endl;
    return Ok(kTaskComplete);
}
