#include "utils.hpp"

std::size_t utils::get_stringstream_size(std::stringstream &ss) {
    ss.seekg(0, std::ios::end);
    std::size_t size = ss.tellg();
    ss.seekg(0, std::ios::beg);
    return size;
}