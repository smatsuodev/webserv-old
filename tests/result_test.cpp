#include "utils/result.hpp"
#include <gtest/gtest.h>

TEST(ResultTest, constructOkInt) {
    Result<int, std::string> target = Ok(0);
    EXPECT_TRUE(target.isOk());
    EXPECT_FALSE(target.isErr());
}

TEST(ResultTest, constructErrString) {
    Result<int, std::string> target = Err<std::string>("error");
    EXPECT_TRUE(target.isErr());
    EXPECT_FALSE(target.isOk());
}

TEST(ResultTest, eqSameOks) {
    EXPECT_TRUE(Ok(1) == Ok(1));
}

TEST(ResultTest, eqDistinctOks) {
    EXPECT_FALSE(Ok(1) == Ok(2));
}

TEST(ResultTest, neDistinctOks) {
    EXPECT_TRUE(Ok(1) != Ok(2));
}

TEST(ResultTest, neSameOks) {
    EXPECT_FALSE(Ok(1) != Ok(1));
}

TEST(ResultTest, eqErrs) {
    EXPECT_TRUE(Err("error") == Err("error"));
}

TEST(ResultTest, neErrs) {
    EXPECT_FALSE(Err("error") != Err("error"));
}

TEST(ResultTest, eqSameOkResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Ok(1);
    EXPECT_TRUE(res1 == res2);
}

TEST(ResultTest, eqDistinctOkResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Ok(2);
    EXPECT_FALSE(res1 == res2);
}

TEST(ResultTest, neDistinctOkResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Ok(2);
    EXPECT_TRUE(res1 != res2);
}

TEST(ResultTest, neSameOkResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Ok(1);
    EXPECT_FALSE(res1 != res2);
}

TEST(ResultTest, eqErrResults) {
    Result<int, std::string> res1 = Err<std::string>("error");
    Result<int, std::string> res2 = Err<std::string>("error");
    EXPECT_TRUE(res1 == res2);
}

TEST(ResultTest, neErrResults) {
    Result<int, std::string> res1 = Err<std::string>("error");
    Result<int, std::string> res2 = Err<std::string>("error");
    EXPECT_FALSE(res1 != res2);
}

TEST(ResultTest, eqOkAndErrResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Err<std::string>("error");
    EXPECT_FALSE(res1 == res2);
    EXPECT_FALSE(res2 == res1);
}

TEST(ResultTest, neOkAndErrResults) {
    Result<int, std::string> res1 = Ok(1);
    Result<int, std::string> res2 = Err<std::string>("error");
    EXPECT_TRUE(res1 != res2);
    EXPECT_TRUE(res2 != res1);
}

TEST(ResultTest, unwrapOnOk) {
    Result<int, std::string> target = Ok(1);
    EXPECT_EQ(target.unwrap(), 1);
}

TEST(ResultTest, unwrapOnErr) {
    Result<int, std::string> target = Err<std::string>("error");
    EXPECT_THROW(target.unwrap(), std::runtime_error);
}

TEST(ResultTest, unwrapOrOnOk) {
    Result<std::string, int> target = Ok<std::string>("ok");
    EXPECT_EQ(target.unwrapOr("error"), "ok");
}

TEST(ResultTest, unwrapOrOnErr) {
    Result<std::string, int> target = Err(1);
    EXPECT_EQ(target.unwrapOr("error"), "error");
}

TEST(ResultTest, unwrapErrOnErr) {
    Result<int, std::string> target = Err<std::string>("error");
    EXPECT_EQ(target.unwrapErr(), "error");
}

TEST(ResultTest, unwrapErrOnOk) {
    Result<int, std::string> target = Ok(1);
    EXPECT_THROW(target.unwrapErr(), std::runtime_error);
}

Result<int, std::string> addOneIf(const Result<int, std::string> &res) {
    int value = TRY(res);

    return Ok(value + 1);
}

TEST(ResultTest, tryOk) {
    Result<int, std::string> expect = Ok(2);
    EXPECT_EQ(expect, addOneIf(Ok(1)));
}

TEST(ResultTest, tryErr) {
    Result<int, std::string> expect = Err<std::string>("error");
    EXPECT_EQ(expect, addOneIf(Err<std::string>("error")));
}

int doubleIf(const Result<int, std::string> &res, int default_value) {
    int value = TRY_OR(res, default_value);

    return value * 2;
}

TEST(ResultTest, tryOrOk) {
    Result<int, std::string> target = Ok(1);
    EXPECT_EQ(doubleIf(target, 0), 2);
}

TEST(ResultTest, tryOrErr) {
    Result<int, std::string> target = Err<std::string>("error");
    EXPECT_EQ(doubleIf(target, 0), 0);
}
