#include "write_file.hpp"
#include <unistd.h>

IWriteFileCallback::~IWriteFileCallback() {}

WriteFile::WriteFile(IOTaskManager &manager, int fd, const std::string &data_to_write, IWriteFileCallback *cb)
    : IOTask(manager, fd), data_to_write_(data_to_write), cb_(cb) {
}

Result<IOTaskResult, std::string> WriteFile::execute() {
    write(fd_, data_to_write_.c_str(), data_to_write_.size());
    if (cb_ != NULL)
        cb_->trigger();
    return Ok(kTaskComplete);
}

WriteFile::~WriteFile() {
    delete cb_;
}

CloseConnectionCallback::CloseConnectionCallback(IContext *ctx) : ctx_(ctx) {}

Result<types::Unit, std::string> CloseConnectionCallback::trigger() {
    close(ctx_->getClientFd());
    return Ok(unit);
}
