// 18_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { };

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { return 0; } // 행위 기반 검증 X
    virtual int Add(int times, Element x) { return 0; } // 행위 기반 검증 O
};

// 가상 함수로 이루어진 부모 클래스도, 테스트 대역으로 교체할 수 있습니다.
class MockCalc : public Calc {
public:
    // 순수 가상 함수가 아닌 경우,
    // 부모가 제공하는 가상 함수 중에서 행위 기반 검증을 수행하고자 하는 메소드에 대해서만 MOCK_METHOD 하면 됩니다.
    // int Add(int times, Element x) override
    MOCK_METHOD(int, Add, (int times, Element x), (override));

    // 문제점
    // : MOCK_METHOD 한 메소드와 동일한 이름의 함수가 부모에 존재하면,
    //   MOCK_METHOD에 의해서 가려지는 현상이 발생합니다.
    using Calc::Add; // !!!
};

// * 인자 매칭을 사용자 정의 타입에 대해서 수행할 경우,
//   연산자 오버로딩이 필요합니다.
bool operator==(const Element& lhs, const Element& rhs)
{
    return true;
}

TEST(SampleTest, Sample)
{
    MockCalc mock;

    mock.Add(Element {});
    mock.Add(42, Element {});

    EXPECT_CALL(mock, Add(42, Element {})); // 행위 기반 검증!
}
