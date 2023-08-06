#include "MyMath.h"

#include <gtest/gtest.h>

TEST(MathTest, AddAssertions)
{
    math::Math math;
    int ret = math.add(1, 2);
    // Expect equality.
    EXPECT_EQ(3, ret);
}

TEST(MathTest, SubAssertions)
{
    math::Math math;
    int ret = math.add(10, 2);
    // Expect equality.
    EXPECT_EQ(8, ret);
}