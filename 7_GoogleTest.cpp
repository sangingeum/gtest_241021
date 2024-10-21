// 7_GoogleTest.cpp
#include <gtest/gtest.h>

// 1. 테스트 비활성화
// => 테스트를 비활성화하면, 테스트를 수행하지 않고, 결과에도 포함되지 않습니다.
//    비활성화된 테스트가 존재한다는 사실을 결과를 통해서 알립니다.
// => 테스트를 비활성화하기 위해서, 주석처리하면, "잊혀진 테스트"가 됩니다.

// => Google Test 에서는 테스트 스위트 이름 또는 테스트 케이스의 이름이
//    DISABLED_ 접두를 가지는 경우, 비활성화됩니다
// => 비활성화된 테스트를 수행할 수 있는 옵션이 존재합니다.
//  $ ./a.out --gtest_also_run_disabled_tests

TEST(ImageProcessorTest, DISABLED_ResizeImage)
{
    FAIL() << "작성 중입니다.";
}

class DISABLED_SampleTest : public testing::Test { };
TEST_F(DISABLED_SampleTest, foo) { }
TEST_F(DISABLED_SampleTest, goo) { }
TEST_F(DISABLED_SampleTest, hoo) { }

// 2. 테스트 필터
// => 원하는 테스트를 선택적으로 수행할 수 있습니다.

// $ ./a.out --gtest_filter=ImageProcessorTest.foo

// - 여러개의 테스트 케이스를 :을 통해 나열할 수 있습니다.
// $ ./a.out --gtest_filter=ImageProcessorTest.foo:ImageTest.goo

TEST(ImageTest, foo) { }
TEST(ImageTest, goo) { }
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }
