// 20_Hamcrest.cpp
// => Hamcrest Matcher
//  : 비교 표현의 확장 라이브러리
//   - Google Mock을 통해서 제공되고 있습니다.
//  1) Matcher를 이용해서, 행위 기반 검증에서 인자 매칭을 검증할 때 사용합니다.
//  2) Matcher를 이용해서, 상태 기반 검증을 수행할 수 있습니다.
//    => ASSERT_THAT / EXPECT_THAT

#include <gmock/gmock.h>

class User {
    std::string name = "xTom";
    int age = 42;

public:
    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

using testing::Lt;
using testing::StartsWith;
using testing::StrCaseEq;

// https://google.github.io/googletest/reference/matchers.html
TEST(UserTest, Sample)
{
    User user;

    // ...
    EXPECT_EQ(user.GetName(), "Tom") << "실패!";
    EXPECT_THAT(user.GetName(), StartsWith("T")) << "실패!";
    EXPECT_THAT(user.GetName(), StrCaseEq("TOM")) << "실패!";

    EXPECT_LT(user.GetAge(), 100);
    EXPECT_THAT(user.GetAge(), Lt(100));
}
