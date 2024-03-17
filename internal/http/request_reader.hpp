#ifndef REQUEST_READER_HPP
#define REQUEST_READER_HPP

#include "utils/result.hpp"
#include "utils/unit.hpp"
#include "utils/utils.hpp"
#include <sstream>
#include <string>

class RequestReader {
public:
    RequestReader(int fd);
    RequestReader(int fd, std::size_t chunk_size);
    ~RequestReader();
    // Read a CRLF-terminated line
    // The returned line includes the CRLF if present
    Result<std::string, std::string> getline();
    Result<std::string, std::string> read(std::size_t n);
    bool eof() const;

private:
    static const std::size_t kDefaultChunkSize = utils::kKiB;
    const int fd_;
    std::size_t chunk_size_;
    std::stringstream buffer_;
    char *chunk_buf_;
    bool eof_;

    Result<std::size_t, std::string> loadSingleChunk();
};

#endif //REQUEST_READER_HPP
