#ifndef TASK_INTERFACE_HPP
#define TASK_INTERFACE_HPP

enum IoTaskResult {
    kTaskPending,
    kTaskComplete,
};

class IoTask {
public:
    virtual IoTaskResult execute() = 0;
};

#endif //TASK_INTERFACE_HPP
