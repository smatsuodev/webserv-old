#ifndef IO_TASK_HPP
#define IO_TASK_HPP

#include "utils/result.hpp"
#include <string>

enum IOTaskResult {
    kTaskSuspend,
    kTaskComplete,
};

class IOTaskManager;

class IOTask {
public:
    IOTask(IOTaskManager &m, int fd);
    virtual ~IOTask();
    virtual Result<IOTaskResult, std::string> execute() = 0;

protected:
    int const fd;
    IOTaskManager &manager; // NOLINT(*-avoid-const-or-ref-data-members)
};

#endif //IO_TASK_HPP
