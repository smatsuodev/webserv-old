#include "accept.hpp"
#include "utils/result.hpp"
#include <iostream>
#include <sys/socket.h>

Accept::Accept(IOTaskManager &m, int fd) : IOTask(m, fd) {}

Accept::~Accept() {
}

Result<IOTaskResult, std::string> Accept::execute() {
    // クライアントからの接続を受け入れる
    int client_fd = accept(fd, NULL, NULL);
    if (client_fd < 0) {
        return Err<std::string>("Error: Accept failed\n");
    }
    std::cout << "Client connected\n";
    return Ok(kTaskSuspend);
}
