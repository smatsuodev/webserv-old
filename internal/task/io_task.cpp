#include "io_task.hpp"
#include "io_task_manager.hpp"

IOTask::IOTask(IOTaskManager &m, int fd) : fd(fd), manager_(m) {
    m.addTask(this);
}

IOTask::~IOTask() {
    manager_.removeTask(this);
}
