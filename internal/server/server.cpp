#include "server.hpp"
#include "task/accept.hpp"
#include "task/io_task_manager.hpp"
#include <iostream>

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

int Server::createServerSocket() {
    std::cout << "create server socket" << std::endl;
    return 0;
}

void Server::start(void) {
    std::cout << "start called ! " << std::endl;

    int fd = createServerSocket();

    IOTaskManager m;
    Accept *task = new Accept(m, fd); // タスクの登録はコンストラクタがやる
    m.executeTasks();
}
