#include "stream_buffer_switcher.hpp"
#include "hello/hello.hpp"
#include <gtest/gtest.h>

TEST(HelloTest, output) {
    std::stringstream ss;
    StreamBufferSwitcher sbs(std::cout, ss.rdbuf());
    Hello();
    EXPECT_EQ(ss.str(), "Hello, World!\n");
}