#ifndef IO_TASK_HPP
#define IO_TASK_HPP

#include "utils/result.hpp"
#include <string>

enum IOTaskResult {
    kTaskSuspend,
    kTaskComplete,
};

class IOTaskManager;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IOTask {
public:
    const int fd_;

    IOTask(IOTaskManager &m, int fd);
    virtual ~IOTask();
    virtual Result<IOTaskResult, std::string> execute() = 0;

protected:
    IOTaskManager &manager;
};

#endif //IO_TASK_HPP
