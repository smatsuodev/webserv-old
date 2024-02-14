#ifndef TASK_INTERFACE_HPP
#define TASK_INTERFACE_HPP

#include <string>

template<typename T, typename E>
class Result;

enum IOTaskResult {
    kTaskSuspend,
    kTaskComplete,
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IOTask {
public:
    virtual ~IOTask() = 0;
    virtual Result<IOTaskResult, std::string> execute() = 0;
};

#endif //TASK_INTERFACE_HPP
