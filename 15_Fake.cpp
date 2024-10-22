// 15_Fake.cpp
#include <string>

class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name { s }
        , age { n }
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class Repository {
    IDatabase* database;

public:
    Repository(IDatabase* p)
        : database { p }
    {
    }

    void Save(User* user)
    {
        // ...
        database->SaveUser(user->GetName(), user);
        // ...
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};

#include <gtest/gtest.h>
#include <map>

// Fake Object Pattern
// 의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
// 방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서, 테스트 되지 않은 요구사항을 검증합니다.

class FakeDatabase : public IDatabase {
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name) override
    {
        return data[name];
    }
};

TEST(RepositoryTest, Save)
{
    FakeDatabase database;
    Repository repo { &database };
    std::string test_name = "test_name";
    int test_age = 42;
    User expected { test_name, test_age };

    repo.Save(&expected);
    User* actual = repo.Load(test_name);

    EXPECT_EQ(expected, *actual);
}
