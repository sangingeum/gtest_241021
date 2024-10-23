// 21_행위기반검증2.cpp
class Dog {
public:
    virtual ~Dog() { }

    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Fourth, (), (override));
};

void Process(Dog* p)
{
    p->First();
    p->Second();
    p->Third();
    p->Fourth();
}

// 4. 호출 순서
//  : First -> Second -> Third -> Fourth

// => testing::InSequence 객체
using testing::InSequence;

TEST(DogTest, Sample1)
{
    InSequence seq; // 해당 객체가 존재하면, 순서를 검증합니다.
    MockDog mock;

    EXPECT_CALL(mock, First());
    EXPECT_CALL(mock, Second());
    EXPECT_CALL(mock, Third());
    EXPECT_CALL(mock, Fourth());

    Process(&mock);
}

void Process2(Dog* p)
{
    p->First();

    p->Third();
    p->Second();

    p->Fourth();
}

// First ---> Second -> Fourth   ; s1
//       |
//       ---> Third              ; s2
// => testing::Sequence
//    EXPECT_CALL(..).InSequence(..)

using testing::Sequence;

TEST(DogTest, Sample2)
{
    Sequence s1, s2;
    MockDog mock;

    EXPECT_CALL(mock, First()).InSequence(s1, s2);
    EXPECT_CALL(mock, Second()).InSequence(s1);
    EXPECT_CALL(mock, Third()).InSequence(s2);
    EXPECT_CALL(mock, Fourth()).InSequence(s1);

    Process2(&mock);
}

class Car {
public:
    virtual ~Car() { }

    virtual void f1() { }
    virtual void f2() { }
    virtual void f3() { }
    virtual void f4() { }
    virtual void f5() { }
};

class MockCar : public Car {
public:
    MOCK_METHOD(void, f1, (), (override));
    MOCK_METHOD(void, f2, (), (override));
    MOCK_METHOD(void, f3, (), (override));
    MOCK_METHOD(void, f4, (), (override));
    MOCK_METHOD(void, f5, (), (override));
};

void foo(Car* p)
{
    p->f1();
    p->f2();
    p->f3();
    p->f4();
    p->f5();
}

// f1 ---> f2               ; s1
//    |
//    ---> f3 --> f5        ; s2
//    |
//    ---> f4               ; s3
TEST(CarTest, Sample)
{
    Sequence s1, s2, s3;
    MockCar mock;

    EXPECT_CALL(mock, f1).InSequence(s1, s2, s3);
    EXPECT_CALL(mock, f2).InSequence(s1);
    EXPECT_CALL(mock, f3).InSequence(s2);
    EXPECT_CALL(mock, f4).InSequence(s3);
    EXPECT_CALL(mock, f5).InSequence(s2);

    foo(&mock);
}
