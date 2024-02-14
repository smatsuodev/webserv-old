#ifndef TASK_INTERFACE_HPP
#define TASK_INTERFACE_HPP

#include <string>

template<typename T, typename E>
class Result;

enum IoTaskResult {
    kTaskPending,
    kTaskComplete,
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class IoTask {
public:
    virtual ~IoTask() = 0;
    virtual Result<IoTaskResult, std::string> execute() = 0;
};

#endif //TASK_INTERFACE_HPP
