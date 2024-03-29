#ifndef IOTASKMANAGER_HPP
#define IOTASKMANAGER_HPP

#include "io_task.hpp"
#include <map>
#include <vector>

class IOTaskManager {
public:
    IOTaskManager();
    virtual ~IOTaskManager();
    void executeTasks();
    virtual void addTask(IOTask *task);
    virtual void removeTask(IOTask *task);

private:
    std::vector<IOTask *> tasks_;
};

#endif
