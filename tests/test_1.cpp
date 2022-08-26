#include <gtest/gtest.h>

TEST(tt, addTest){
    const int result = 42 + 11;
    EXPECT_EQ(result, 53);
}

TEST(tt, subTest){
    const int result = 42 - 11;
    EXPECT_EQ(result, 31);
}