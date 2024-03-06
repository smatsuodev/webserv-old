#include "io_task.hpp"
#include "io_task_manager.hpp"

IOTask::IOTask(IOTaskManager &m, int fd) : fd(fd), manager(m) {
    m.addTask(this);
}

IOTask::~IOTask() {
    manager.removeTask(this);
}

int IOTask::getFd() const {
    return fd;
}
