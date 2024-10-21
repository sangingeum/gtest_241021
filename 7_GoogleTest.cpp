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
// => 테스트의 이름을 잘 구성하는 것이 좋습니다.
//    예) 테스트의 성격에 따라 다른 접두를 사용하자.
//       PA_
//       PB_

// $ ./a.out --gtest_filter=ImageProcessorTest.foo

// - 여러개의 테스트 케이스를 :을 통해 나열할 수 있습니다.
// $ ./a.out --gtest_filter=ImageProcessorTest.foo:ImageTest.goo

// - 와일드 카드(*)를 지원합니다.
// $ ./a.out --gtest_filter=*.foo
// $ ./a.out --gtest_filter=Image*.foo

// $ ./a.out --gtest_filter=Image*.foo:-ImageProcessorTest.foo

TEST(ImageTest, foo) { }
TEST(ImageTest, goo) { }
TEST(ImageTest, hoo) { }

TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }

// 3. 반복 / 무작위
// => 모든 테스트는 몇 번을 수행하든, 순서에 상관없이 항당 동일한 결과가 나와야 합니다.
//  "신뢰성"

// $ ./a.out --gtest_repeat=10 --gtest_shuffle --gtest_break_on_failure
//  : --gtest_break_on_failure
//  테스트가 실패하면, 테스트 프로그램을 강제적으로 종료합니다.

int n = 0;
TEST(SampleTest, foo)
{
    if (n++ == 5) {
        FAIL();
    }
}

// Google Test(1.10 이전)
// - Test Case
//  - Test
//  - Test
//  - Test

// Google Test(1.10 이후)
// - Test Suite
//  - Test
//  - Test
//  - Test

// xUnit Test Framework
// - Test Suite
//   - Test Case
//   - Test Case
//   - Test Case

// 4. 테스트 결과 포맷터(Test Result Formatter)
// => 테스트의 결과를 XML 형식으로 export 할 수 있습니다. - xUnit Test Framework
//  $ ./a.out --gtest_output=xml
// => 테스트의 결과를 JSON 형식으로 export 할 수 있습니다. - Google Test
//  $ ./a.out --gtest_output=json
