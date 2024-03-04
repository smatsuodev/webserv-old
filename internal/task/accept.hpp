#ifndef ACCEPT_HPP
#define ACCEPT_HPP

#include "io_task.hpp"
#include "io_task_manager.hpp"

class Accept : public IOTask {
public:
    Accept(IOTaskManager &m, int fd);
    ~Accept();
    virtual Result<IOTaskResult, std::string> execute();

private:
};

#endif
