// 9_FriendTest.cpp

class User {
public:
    int age = 42;

    int GetAge() const { return age; }

    void foo() { age = 100; }
};

#include <gtest/gtest.h>

TEST(UserTest, foo)
{
    User user;

    user.foo();

    EXPECT_EQ(user.GetAge(), 100);
}
