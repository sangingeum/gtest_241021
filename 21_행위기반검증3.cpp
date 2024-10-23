// 21_행위기반검증3.cpp
#include <iostream>
using namespace std;

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) { return a + b; }
    virtual int Sub(int a, int b) { return a - b; }
};

void Process(Calc* p)
{
    if (p->Add(10, 20) == 30) {
        int result = p->Sub(100, 50);
        std::cout << "result: " << result << std::endl;
    }
}

#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));
};

// * EXPECT_CALL과 ON_CALL을 동시에 사용하고 있습니다.
// => EXPECT_CALL을 통해, ON_CALL을 사용하지 않고, 결과를 제어(Delegating)할 수 있습니다.
//  - EXPECT_CALL(...)
//    .WillOnce(Return(30))
//    .WillRepeatedly(Return(30));

using testing::NiceMock;
using testing::Return;

TEST(CalcTest, Process)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20)).WillOnce(Return(30));
    EXPECT_CALL(mock, Sub(100, 50)).WillOnce(Return(50));

    Process(&mock);
}

// * 중요: EXPECT_CALL().WillOnce/WillRepeatedly를 사용하면, Times에 영향을 줍니다.
//  -  WillOnce: N
//  -  WillRepeatedly: AtLeast

// - EXPECT_CALL(...)
// => EXPECT_CALL(...).Times(1)

// - EXPECT_CALL(...).WillOnce();
// => EXPECT_CALL(...).Times(1);

// - EXPECT_CALL(...).WillOnce().WillOnce();
// => EXPECT_CALL(...).Times(2)

// - EXPECT_CALL(...).WillOnce().WillOnce().WillOnce();
// => EXPECT_CALL(...).Times(3);

// - EXPECT_CALL(...).WillRepeatedly();
// => EXPECT_CALL(...).Times(AtLeast(0));

// - EXPECT_CALL(...).WillOnce().WillRepeatedly();
// => EXPECT_CALL(...).Times(AtLeast(1));

// - EXPECT_CALL(...).WillOnce().WillOnce().WillOnce().WillRepeatedly();
// => EXPECT_CALL(...).Times(AtLeast(3));

TEST(CalcTest, Process2)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillOnce(Return(100))
        .WillOnce(Return(100))
        .WillOnce(Return(100))
        .WillRepeatedly(Return(30));

    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
}

#if 0
TEST(CalcTest, Process)
{
    MockCalc mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
}
#endif
