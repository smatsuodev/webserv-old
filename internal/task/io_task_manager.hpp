#ifndef IOTASKMANAGER_HPP
#define IOTASKMANAGER_HPP

#include "io_task.hpp"
#include <map>
#include <vector>

class IOTaskManager {
public:
    IOTaskManager();
    ~IOTaskManager();
    void executeTasks();
    void addTask(IOTask *task);
    void removeTask(IOTask *task);

private:
    std::vector<IOTask *> tasks_;
};

#endif
