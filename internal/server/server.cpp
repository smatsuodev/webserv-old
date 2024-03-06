#include "server.hpp"
#include "task/accept.hpp"
#include "task/io_task_manager.hpp"
#include "utils/unit.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server() {
    std::cout << "Server constructor called" << std::endl;
}

Server::Server(const Server &other) {
    std::cout << "Server copy constructor called" << std::endl;
    *this = other;
}

Server::~Server() {
    std::cout << "Server destructor called" << std::endl;
}

Server &Server::operator=(const Server &other) {
    return *this;
}

Result<int, std::string> Server::createServerSocket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        return Err<std::string>("Error: Failed to create socket\n");
    }

    // サーバーソケットの設定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    // ソケットをアドレスにバインド
    if (bind(server_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        close(server_fd);
        return Err<std::string>("Error: Bind failed\n");
    }

    // 接続を待ち受ける
    if (listen(server_fd, SOMAXCONN) < 0) {
        close(server_fd);
        return Err<std::string>("Error: Listen failed\n");
    }
    return Ok(server_fd);
}

Result<types::Unit, std::string> Server::start(void) {
    std::cout << "start called ! " << std::endl;
    int fd = createServerSocket().unwrap();

    IOTaskManager m;
    Handler *handler = new Handler();
    new Accept(m, fd, new AcceptCallback(m, handler)); // タスクの登録はコンストラクタがやる
    m.executeTasks();
    delete handler;
    return Ok(unit);
}
