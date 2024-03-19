#include <gtest/gtest.h>
#include "http/request_parser.hpp"

TEST(ParseHeaderFieldLineErr, noColon) {
    const auto result = RequestParser::parseHeaderFieldLine("Host");
    EXPECT_TRUE(result.isErr());
}

TEST(ParseHeaderFieldLineErr, emptyFieldName) {
    const auto result = RequestParser::parseHeaderFieldLine(": value");
    EXPECT_TRUE(result.isErr());
}

TEST(ParseHeaderFieldLineErr, spaceBeforeFieldName) {
    const auto result = RequestParser::parseHeaderFieldLine(" Host: value");
    EXPECT_TRUE(result.isErr());
}

TEST(ParseHeaderFieldLineErr, fieldNameContainsSpace) {
    const auto result = RequestParser::parseHeaderFieldLine("Field Name: value");
    EXPECT_TRUE(result.isErr());
}

// RFC 9112: No whitespace is allowed between the field name and colon
TEST(ParseHeaderFieldLineErr, spaceBeforeColon) {
    const auto result = RequestParser::parseHeaderFieldLine("Host : value");
    EXPECT_TRUE(result.isErr());
}

TEST(ParseHeaderFieldLineOk, normal) {
    const auto result = RequestParser::parseHeaderFieldLine("Host: example.com");
    EXPECT_TRUE(result.isOk());
    EXPECT_EQ(result.unwrap().first, "Host");
    EXPECT_EQ(result.unwrap().second, "example.com");
}

TEST(ParseHeaderFieldLineOk, noSpaceAfterColon) {
    const auto result = RequestParser::parseHeaderFieldLine("Host:example.com");
    EXPECT_TRUE(result.isOk());
    EXPECT_EQ(result.unwrap().first, "Host");
    EXPECT_EQ(result.unwrap().second, "example.com");
}

TEST(ParseHeaderFieldLineOk, spacesAroundValue) {
    const auto result = RequestParser::parseHeaderFieldLine("Host:   example.com   ");
    EXPECT_TRUE(result.isOk());
    EXPECT_EQ(result.unwrap().first, "Host");
    EXPECT_EQ(result.unwrap().second, "example.com");
}

TEST(ParseHeaderFieldLineOk, tabAroundValue) {
    const auto result = RequestParser::parseHeaderFieldLine("Host:\texample.com\t");
    EXPECT_TRUE(result.isOk());
    EXPECT_EQ(result.unwrap().first, "Host");
    EXPECT_EQ(result.unwrap().second, "example.com");
}

TEST(ParseHeaderFieldLineOk, spaceInValue) {
    const auto result = RequestParser::parseHeaderFieldLine("User-Agent: A browser");
    EXPECT_TRUE(result.isOk());
    EXPECT_EQ(result.unwrap().first, "User-Agent");
    EXPECT_EQ(result.unwrap().second, "A browser");
}