// 1_시작.cpp
#include <gtest/gtest.h>

// Google Test의 main은 아래 형태로 제공되어야 합니다.
// - Google Test는 다양한 환경에서 동작하는 main을 이미 제공하고 있습니다.
// - 라이브러리에 main을 포함시키면, 매번 main을 작성할 필요가 없습니다.
#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
#endif
