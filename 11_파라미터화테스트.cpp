// 11_파라미터화테스트.cpp
#include <regex>
#include <string>

bool IsValidEmail(const std::string& email)
{
    const std::regex pattern { R"((\w+)(\.|\_)?(\w*)@(\w+)(\.(\w+))+)" };
    return std::regex_match(email, pattern);
}

#include <gtest/gtest.h>

TEST(EmailTest, IsValidEmail)
{
    EXPECT_TRUE(IsValidEmail("valid@gmail.com"));
}
