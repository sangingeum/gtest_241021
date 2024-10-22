// 11_파라미터화테스트2.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

// 2, 3, 5, 7, 11, 13, 17, 23, 29 ...
// 위의 데이터를 파라미터화 테스트를 통해 직접 작성해보세요.
#include <gtest/gtest.h>

class PrimeTest : public testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(2, 3, 5, 7, 11, 13, 17, 23, 29));

TEST_P(PrimeTest, IsPrime)
{
    EXPECT_TRUE(IsPrime(GetParam()));
}
