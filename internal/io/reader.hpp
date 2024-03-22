#ifndef READER_HPP
#define READER_HPP

#include <string>
#include "utils/result.hpp"

class IReader {
public:
    virtual ~IReader();
    // Read up to n bytes into buf
    // Return the number of bytes read, or an error if one occurred
    virtual Result<std::size_t, std::string> read(char *buf, std::size_t n) = 0;
};

class FdReader : public IReader {
public:
    explicit FdReader(int fd);
    virtual ~FdReader();
    virtual Result<std::size_t, std::string> read(char *buf, std::size_t n);

private:
    int fd_;
};

#endif //READER_HPP
