#include "stream_buffer_switcher.hpp"

StreamBufferSwitcher::StreamBufferSwitcher(std::ostream &os, std::streambuf *new_buffer)
    : os_(os), old_buffer_(os.rdbuf(new_buffer)) {}

StreamBufferSwitcher::~StreamBufferSwitcher() {
    os_.rdbuf(old_buffer_);
}
