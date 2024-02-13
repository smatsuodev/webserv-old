#include "utils/option.hpp"
#include <gtest/gtest.h>

TEST(OptionTest, constructSomeInt) {
    Option<int> target = Some(0);
    EXPECT_TRUE(target.isSome());
    EXPECT_FALSE(target.isNone());
}

TEST(OptionTest, constructNone) {
    Option<int> target = None;
    EXPECT_TRUE(target.isNone());
    EXPECT_FALSE(target.isSome());
}

TEST(OptionTest, eqSameSomes) {
    EXPECT_TRUE(Some(1) == Some(1));
}

TEST(OptionTest, eqDistinctSomes) {
    EXPECT_FALSE(Some(1) == Some(2));
}

TEST(OptionTest, neDistinctSomes) {
    EXPECT_TRUE(Some(1) != Some(2));
}

TEST(OptionTest, neSameSomes) {
    EXPECT_FALSE(Some(1) != Some(1));
}

TEST(OptionTest, eqNones) {
    EXPECT_TRUE(types::None() == types::None());
}

TEST(OptionTest, neNones) {
    EXPECT_FALSE(types::None() != types::None());
}

TEST(OptionTest, eqSameSomeOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = Some(1);
    EXPECT_TRUE(op1 == op2);
}

TEST(OptionTest, eqDistinctSomeOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = Some(2);
    EXPECT_FALSE(op1 == op2);
}

TEST(OptionTest, neDistinctSomeOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = Some(2);
    EXPECT_TRUE(op1 != op2);
}

TEST(OptionTest, neSameSomeOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = Some(1);
    EXPECT_FALSE(op1 != op2);
}

TEST(OptionTest, eqNoneOptions) {
    Option<int> op1 = None;
    Option<int> op2 = None;
    EXPECT_TRUE(op1 == op2);
}

TEST(OptionTest, neNoneOptions) {
    Option<int> op1 = None;
    Option<int> op2 = None;
    EXPECT_FALSE(op1 != op2);
}

TEST(OptionTest, eqSomeAndNoneOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = None;
    EXPECT_FALSE(op1 == op2);
    EXPECT_FALSE(op2 == op1);
}

TEST(OptionTest, neSomeAndNoneOptions) {
    Option<int> op1 = Some(1);
    Option<int> op2 = None;
    EXPECT_TRUE(op1 != op2);
    EXPECT_TRUE(op2 != op1);
}
