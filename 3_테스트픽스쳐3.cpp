// 3_테스트픽스쳐3.cpp
class Calc {
public:
    // Calc(int n) { } // !!!

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

//---
#include <gtest/gtest.h>

// 2. Test Fixture를 설치하는 방법
// 3) Implicit Set up(암묵적 설치)
// => xUnit Test Framework이 제공하는 기능입니다.
// 방법: 여러 테스트케이스 안에서 같은 테스트 픽스쳐 설치의 코드를 암묵적으로 호출되는 약속된 함수를 통해서 처리합니다.
//  - 명시적인 테스트 스위트 클래스가 제공되어야 합니다.
//  * 장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 테스트 케이스안에서 제거할 수 있습니다.
//  * 단점: 픽스쳐 설치의 과정이 테스트 케이스 외부에 존재하기 때문에
//         테스트케이스 만으로 인과관계를 분석하기 어려울 수 있습니다.

class CalcTest : public testing::Test {
protected:
    Calc* calc;

    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
        calc = new Calc;
    }
};

#define SPEC(msg) printf("[SPEC] %s\n", msg)

TEST_F(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, 4의 결과가 나오는지 여부를 검증합니다.");

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    // xUnit Test Framework은 다양한 단언문을 제공하고 있습니다.
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST_F(CalcTest, PressMinus)
{
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(5);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 5) << "10 - 5를 하였을 때";
}
