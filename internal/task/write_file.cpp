#include "write_file.hpp"
#include <unistd.h>

IWriteFileCallback::~IWriteFileCallback() {}

WriteFile::WriteFile(IOTaskManager &manager, int fd, const std::string& data_to_write, IWriteFileCallback *cb)
    : IOTask(manager, fd), data_to_write_(data_to_write), cb_(cb) {
}

Result<IOTaskResult, std::string> WriteFile::execute() {
    write(fd, data_to_write_.c_str(), data_to_write_.size());
    cb_->trigger();
    return Ok(kTaskComplete);
}

WriteFile::~WriteFile() {
    delete cb_;
}

WriteFileCallback::WriteFileCallback(int fd) : fd_(fd) {}

Result<types::Unit, std::string> WriteFileCallback::trigger() {
    close(fd_);
    return Ok(unit);
}
