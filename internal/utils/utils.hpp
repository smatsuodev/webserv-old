#ifndef UTILS_HPP
#define UTILS_HPP

#include <sstream>
#include <string>

namespace utils {
    const unsigned int kKiB = 1024;        // 1 KiB = 1024 bytes
    const unsigned int kMiB = 1024 * kKiB; // 1 MiB = 1024 KiB

    template<class T>
    std::string toString(T value) {
        std::stringstream ss;
        ss << value;

        return ss.str();
    }
} // namespace utils

#endif //UTILS_HPP
