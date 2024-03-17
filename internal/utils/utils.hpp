#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>

namespace utils {
    const unsigned int kKiB = 1024;        // 1 KiB = 1024 bytes
    const unsigned int kMiB = 1024 * kKiB; // 1 MiB = 1024 KiB

    std::size_t getStringStreamSize(std::stringstream &ss);

    bool startsWith(const std::string &str, const std::string &prefix);
    bool endsWith(const std::string &str, const std::string &suffix);
} // namespace utils

#endif //UTILS_HPP
