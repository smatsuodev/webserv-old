#include "request_reader.hpp"
#include "utils/utils.hpp"
#include <unistd.h>

RequestReader::RequestReader(int fd) : fd_(fd), chunk_size_(kDefaultChunkSize), eof_(false) {
    chunk_buf_ = new char[chunk_size_];
}

RequestReader::RequestReader(int fd, std::size_t chunk_size) : fd_(fd), chunk_size_(chunk_size), eof_(false) {
    chunk_buf_ = new char[chunk_size_];
}

RequestReader::~RequestReader() {
    delete[] chunk_buf_;
}

bool RequestReader::eof() const {
    return eof_ && buffer_.eof();
}

Result<std::string, std::string> RequestReader::getline() {
    while (true) {
        Result<std::size_t, std::string> load_result = loadSingleChunk();
        if (load_result.isErr()) {
            return Err<std::string>(load_result.unwrapErr());
        }

        // TODO: 効率的な実装に変更する
        // 毎回コピー, 検索するのは無駄
        const std::string buf_str = buffer_.str();
        const std::size_t crlf_pos = buf_str.find("\r\n");
        if (crlf_pos != std::string::npos) {
            const std::string line = buf_str.substr(0, crlf_pos + 2);
            buffer_.str(buf_str.substr(crlf_pos + 2));
            return Ok(line);
        }

        // CRLF なしで EOF に到達した場合
        if (eof_) {
            buffer_.clear();
            return Ok(buf_str);
        }
    }
}

Result<std::string, std::string> RequestReader::read(const std::size_t n) {
    while (utils::getStringStreamSize(buffer_) < n && !eof_) {
        Result<std::size_t, std::string> load_result = loadSingleChunk();
        if (load_result.isErr()) {
            return Err<std::string>(load_result.unwrapErr());
        }
    }

    const std::string buf_str = buffer_.str();
    const std::string result = buf_str.substr(0, n);
    buffer_.str(buf_str.substr(n));
    return Ok(result);
}

Result<std::size_t, std::string> RequestReader::loadSingleChunk() {
    const ssize_t read_result = ::read(fd_, chunk_buf_, chunk_size_ - 1);
    if (read_result == -1) {
        return Err<std::string>("failed to read request");
    }
    const std::size_t bytes_read = static_cast<std::size_t>(read_result);
    if (bytes_read == 0) {
        eof_ = true;
        return Ok(bytes_read);
    }

    chunk_buf_[bytes_read] = '\0';
    buffer_ << chunk_buf_;
    return Ok(bytes_read);
}
