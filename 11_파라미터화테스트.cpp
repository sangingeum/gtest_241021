// 11_파라미터화테스트.cpp
#include <regex>
#include <string>

bool IsValidEmail(const std::string& email)
{
    const std::regex pattern { R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)" };
    // return false;
    return std::regex_match(email, pattern);
}

#include <gtest/gtest.h>

// * 파라미터화 테스트(Parameterized Test)
// : xUnit Test Framework이 제공하는 기능입니다.
// 정의: 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
//      테스트 코드 중복의 문제를 해결할 수 있는 기능을 제공합니다.

// 1) 명시적인 테스트 스위트 클래스가 필요합니다.
//         기존> class EmailTest : public testing::Test {};
// 파라미터화테스트> class EmailTest : public testing::TestWithParam<입력데이터타입>
class EmailTest : public testing::TestWithParam<std::string> {
};

// 2) 데이터 셋 정의
// INSTANTIATE_TEST_SUITE_P(prefix, testsuite_class, 데이터 셋)
INSTANTIATE_TEST_SUITE_P(EmailValues, EmailTest,
    testing::Values(
        "a.hoo@naver.com",
        "valid@gmail.com",
        "admin.lee@gmail.com",
        "hello_go@gmail.com"));

// 3) 테스트 케이스
// - TEST
// - TEST_F
// - TEST_P -> 파라미터화 테스트케이스
//   : GetParam()

TEST_P(EmailTest, IsValidEmail)
{
    EXPECT_TRUE(IsValidEmail(GetParam()));
}

#if 0
TEST(EmailTest, IsValidEmail)
{
    EXPECT_TRUE(IsValidEmail("valid@gmail.com"));
    EXPECT_TRUE(IsValidEmail("admin.lee@gmail.com"));
    EXPECT_TRUE(IsValidEmail("hello_go@gmail.com"));
    // ...
}

TEST(EmailTest, IsValidEmail2)
{
    std::string emails[] = {
        "valid@gmail.com",
        "admin.lee@gmail.com",
        "hello_go@gmail.com",
    };

    for (auto e : emails) {
        EXPECT_TRUE(IsValidEmail(e));
    }
}
#endif
