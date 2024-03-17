#include <gtest/gtest.h>
#include "utils/utils.hpp"

TEST(ToStringTest, IntToString) {
    int value = 123;
    std::string expected = "123";
    std::string actual = utils::toString(value);

    ASSERT_EQ(expected, actual);
}
