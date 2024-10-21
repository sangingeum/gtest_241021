// 7_GoogleTest.cpp
#include <gtest/gtest.h>

// 1. 테스트 비활성화
// => 테스트를 비활성화하면, 테스트를 수행하지 않고, 결과에도 포함되지 않습니다.
//    비활성화된 테스트가 존재한다는 사실을 결과를 통해서 알립니다.
// => 테스트를 비활성화하기 위해서, 주석처리하면, "잊혀진 테스트"가 됩니다.

// => Google Test 에서는 테스트 스위트 이름 또는 테스트 케이스의 이름이
//    DISABLED_ 접두를 가지는 경우, 비활성화됩니다.

// TEST(ImageProcessorTest, DISABLED_ResizeImage)
TEST(DISABLED_ImageProcessorTest, ResizeImage)
{
    FAIL() << "작성 중입니다.";
}
