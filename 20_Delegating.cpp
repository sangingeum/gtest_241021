// 20_Delegating.cpp
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

// - MOCK_METHOD한 함수의 결과는 기본값을 반환합니다.
// - Google Mock은 MOCK_METHOD를 수행한 메소드에 대해서,
//   행위 기반 검증 뿐 아니라 결과를 제어할 수 있는 기능을 제공하고 있습니다.
//  => Delegating(위임)
//    : ON_CALL

using testing::NiceMock;
using testing::Return;

TEST(CalcTest, Process)
{
    NiceMock<MockCalc> mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    ON_CALL(mock, Sub(100, 50)).WillByDefault(Return(50));

    EXPECT_CALL(mock, Add(10, 20));
    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
}

using testing::_;

int add(int a, int b) { return a + b; } // 함수

// 함수 객체
struct Adder {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Process3)
{
    NiceMock<MockCalc> mock;

    // ON_CALL(mock, Add).WillByDefault(&add); // 함수
    // ON_CALL(mock, Add).WillByDefault(Adder {}); // 함수 객체
    ON_CALL(mock, Add).WillByDefault([](int a, int b) {
        return a + b;
    }); // 람다 표현식

    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(100, 20) << std::endl;
    std::cout << mock.Add(100, 20) << std::endl;
}

TEST(CalcTest, Process2)
{
    NiceMock<MockCalc> mock;
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    ON_CALL(mock, Add(_, 20)).WillByDefault(Return(30));

    // ON_CALL(mock, Add).WillByDefault(Return(30));
    // 인자와 상관없이 모든 Add의 호출의 결과를 제어합니다.

    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(100, 20) << std::endl;
    std::cout << mock.Add(100, 20) << std::endl;
}

#if 0
TEST(CalcTest, Process)
{
    NiceMock<MockCalc> mock;
    ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));

    // EXPECT_CALL(mock, Add(10, 20));
    // EXPECT_CALL(mock, Sub(100, 50));

    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;

    // Process(&mock);
}
#endif
