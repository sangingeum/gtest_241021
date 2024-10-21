// 6_Assertions.cpp
#include <gtest/gtest.h>

// * Google Test의 단언문은 매크로를 통해서 제공되고 있습니다.

// 1. ASSERT_
//   EQ, NE, LT, GT, LE, GE, TRUE, FALSE ...
//  => 단언문이 실패할 경우, 이후의 테스트 코드를 수행하지 않습니다.
//  => 하나의 테스트 케이스 안에서 여러개의 단언문을 사용할 경우,
//     "죽은 단언문"의 문제가 발생합니다.
//   : xUnit Test Pattern에서는 하나의 테스트케이스 안에 여러개의 단언문을 사용하는 것을
//     지양해야 한다.
//    - 관리해야 하는 테스트 케이스의 수가 늘어나고, 테스트 코드 중복의 문제가 발생합니다.

int foo() { return 420; }
int goo() { return 1000; }

// 2. EXPECT_
//   EQ, NE, LT, GT, LE, GE, TRUE, FALSE ...
//  => 단언문이 실패할 경우, 테스트의 결과는 실패로 결정되지만, 이후의 코드는 계속 수행합니다.
//  => "죽은 단언문"의 문제가 발생하지 않습니다.
TEST(SampleTest, Sample1)
{
    // ...
    EXPECT_EQ(foo(), 42);
    EXPECT_EQ(goo(), 100);
}

#if 0
TEST(SampleTest, Sample1_foo)
{
    // ...
    ASSERT_EQ(foo(), 42);
}

TEST(SampleTest, Sample1_goo)
{
    // ...
    ASSERT_EQ(goo(), 100);
}

#if 0
TEST(SampleTest, Sample1)
{
    // ...
    ASSERT_EQ(foo(), 42);
    ASSERT_EQ(goo(), 100);
}
#endif
#endif

class User {
    std::string name = "Tom";

public:
    std::string GetName() const { return name; }
};

// User* GetUser() { return new User; }
User* GetUser() { return nullptr; }

TEST(UserTest, GetName)
{
    User* user = GetUser();

    // ...

    ASSERT_NE(user, nullptr); // 왜 ASSERT로 작성되어야 하는지 여부를 이해해야 합니다.
    EXPECT_EQ(user->GetName(), "Tom");
}

// 3. C 문자열 비교 단언문
// C 문자열: '\0'문자로 종료되는 char 배열
//  - EXPECT_STREQ/STRNE
//  - EXPECT_STRCASEEQ/STRCASENE ; 대소문자 무시
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";

    // ...
    EXPECT_EQ(s1, s2);

    const char* s3 = "hello";
    const char* s4 = s1.c_str();

    // EXPECT_EQ(s3, s4);
    EXPECT_STREQ(s3, s4);
    const char* s5 = "HELLO";
    EXPECT_STRCASEEQ(s3, s5);
}

// 4. 부동 소수점 타입 비교 단언문
// - EXPECT_FLOAT_EQ/NE
// - EXPECT_DOUBLE_EQ/NE

// - 오차 범위를 직접 정의하고 싶은 경우
//  : EXPECT_NEAR
TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7;

    // EXPECT_EQ(a, b);
    EXPECT_DOUBLE_EQ(a, b);
    EXPECT_NEAR(a, b, 0.0000000001);
}
