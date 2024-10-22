// 1_시작.cpp
#include <gtest/gtest.h>

// Google Test의 main은 아래 형태로 제공되어야 합니다.
// - Google Test는 다양한 환경에서 동작하는 main을 이미 제공하고 있습니다.
// - 라이브러리에 main을 포함시키면, 매번 main을 작성할 필요가 없습니다.

// 정적 라이브러리(.a)
// : 라이브러리가 변경될 때마다, 새롭게 빌드를 수행해야 합니다.
//   라이브러리를 함께 배포할 필요가 없습니다.
// $ ar rcv libgtest.a gtest-all.o gtest_main.o

// 동적 라이브러리(.so)
// : 라이브러리가 변경되어도, 새롭게 빌드를 수행할 필요가 없습니다.
//   라이브러리도 함께 배포되어야 합니다.

#if 0
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
#endif
