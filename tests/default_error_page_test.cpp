#include "config/config.hpp"
#include <fakeit.hpp>
#include <gtest/gtest.h>

using namespace fakeit;

class DefaultErrorPageTest : public ::testing::Test {
protected:
    Config config_;
};

TEST_F(DefaultErrorPageTest, NotFound) {
    const std::string result = config_.getErrorPage(kStatusNotFound);
    const std::string want =
            "<html>"
            "<head><title>404 Not Found</title></head>"
            "<body>"
            "<center><h1>404 Not Found</h1></center>"
            "<hr>"
            "<center>webserv/0.1.0</center>"
            "</body>"
            "</html>";

    EXPECT_EQ(result, want);
}

TEST_F(DefaultErrorPageTest, InternalServerError) {
    const std::string result = config_.getErrorPage(kStatusInternalServerError);
    const std::string want =
            "<html>"
            "<head><title>500 Internal Server Error</title></head>"
            "<body>"
            "<center><h1>500 Internal Server Error</h1></center>"
            "<hr>"
            "<center>webserv/0.1.0</center>"
            "</body>"
            "</html>";

    EXPECT_EQ(result, want);
}