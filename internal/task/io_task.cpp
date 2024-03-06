#include "io_task.hpp"
#include "io_task_manager.hpp"

IOTask::IOTask(IOTaskManager &m, int fd) : manager_(m), fd(fd) {
    m.addTask(this);
}

IOTask::~IOTask() {
    manager_.removeTask(this);
}
