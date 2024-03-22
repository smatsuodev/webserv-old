#include "reader.hpp"
#include <unistd.h>

IReader::~IReader() {
}

FdReader::FdReader(int fd) : fd_(fd) {}

FdReader::~FdReader() {}

Result<std::size_t, std::string> FdReader::read(char *buf, std::size_t n) {
    ssize_t bytes_read = ::read(fd_, buf, n);
    if (bytes_read == -1) {
        return Err(std::string(strerror(errno)));
    }
    return Ok(static_cast<std::size_t>(bytes_read));
}
