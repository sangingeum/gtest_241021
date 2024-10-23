// 21_행위기반검증.cpp
// - 정의: SUT 내부에서 협력 객체를 대상으로 함수의 호출을 통해
//        정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서
#include <string>
#include <vector>

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
    virtual void Print(const std::vector<int>& numbers) = 0;
    virtual void SetAddress(const std::string& address) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
    MOCK_METHOD(void, SetAddress, (const std::string& address), (override));
};

void UsePerson(Person* p)
{
    p->Go(100, 20);
}

// EXPECT_CALL
// 1) EXPECT_CALL을 Act 이전에 작성해야 합니다.
// 2) EXPECT_CALL은 별도로 메세지를 작성할 수 있는 기능을 제공하고 있지 않습니다.
// 3) mock 객체가 파괴될 때, 검증이 수행됩니다.

// 1) 함수 호출 여부
TEST(PersonTest, Sample)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20));
    EXPECT_CALL(mock, Go); // 인자와 상관없이 호출 여부를 판단합니다.

    UsePerson(&mock);
}

TEST(PersonTest, Sample2)
{
    MockPerson* mock = new MockPerson;

    EXPECT_CALL(*mock, Go);

    UsePerson(mock);

    delete mock;
}

// 2) 함수 호출 횟수
//   EXPECT_CALL(...).Times(N)
//   EXPECT_CALL(...).Times(Cardinality)

// * Cardinality
// 1) AtLeast(N) => N번 이상
// 2) AtMost(N)  => N번 이하
// 3) Between(A, B) => A번 이상 B번 이하

using testing::_;
using testing::AtLeast;
using testing::AtMost;
using testing::Between;

void UsePerson2(Person* p)
{
    p->Go(10, 20);
    p->Go(10, 30);
    p->Go(10, 40);
}

TEST(PersonTest, Sample1)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20)); // 1번 호출
    // EXPECT_CALL(mock, Go(10, 20)).Times(3);

    // EXPECT_CALL(mock, Go(10, _)).Times(AtLeast(2));

    EXPECT_CALL(mock, Go(10, 20));
    EXPECT_CALL(mock, Go(10, 30));
    EXPECT_CALL(mock, Go(10, 40));

    UsePerson2(&mock);
}

// 3) 함수 호출 인자
// => Matcher
using testing::Matcher;

using testing::_; // Wildcard

using testing::Ge; // >=
using testing::Gt; // >
using testing::Le; // <=
using testing::Lt; // <

using testing::Eq; // ==
using testing::Ne; // !=

using testing::AllOf; // &&
using testing::AnyOf; // ||

void UsePerson4(Person* p)
{
    p->Go(5, -10);
    p->Go(15, 24);
    p->Go(10, 25); // !!
}

TEST(PersonTest3, Sample2)
{
    MockPerson mock;

    // 첫번째 인자: 5이상(Ge(5))이고, 20미만(Lt(20))입니다.
    // 두번째 인자: 0 미만(Lt(0))이거나, 10(Gt(10))을 초과합니다.
    Matcher<int> arg1 = AllOf(Ge(5), Lt(20));
    Matcher<int> arg2 = AnyOf(Lt(0), (Gt(10)));
    EXPECT_CALL(mock, Go(arg1, arg2)).Times(3);

    UsePerson4(&mock);
}

void UsePerson3(Person* p)
{
    p->Go(5, 10);
    p->Go(15, 24);
    p->Go(10, 20);
}

TEST(PersonTest3, Sample)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20)).Times(3);
    // 첫번째 인자: 5 이상
    // 두번째 인자: 25 미만
    Matcher<int> arg1 = Ge(5);
    Matcher<int> arg2 = Lt(25);
    EXPECT_CALL(mock, Go(arg1, arg2)).Times(3);

    UsePerson3(&mock);
}
