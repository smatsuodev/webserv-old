#include "utils.hpp"

std::size_t utils::getStringStreamSize(std::stringstream &ss) {
    ss.seekg(0, std::ios::end);
    std::size_t size = ss.tellg();
    ss.seekg(0, std::ios::beg);
    return size;
}

bool utils::startsWith(const std::string &str, const std::string &prefix) {
    return str.find(prefix) == 0;
}

bool utils::endsWith(const std::string &str, const std::string &suffix) {
    if (str.size() < suffix.size()) {
        return false;
    }
    return str.rfind(suffix) == (str.size() - suffix.size());
}
