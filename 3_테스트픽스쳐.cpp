// 3_테스트픽스쳐.cpp
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

//---
#include <gtest/gtest.h>

#define SPEC(msg) printf("[SPEC] %s\n", msg)

TEST(CalcTest, PressPlus_TwoPlusTwo_DisplaysFour)
{
    SPEC("2 더하기 2를 하였을 때, 4의 결과가 나오는지 여부를 검증합니다.");
    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    // xUnit Test Framework은 다양한 단언문을 제공하고 있습니다.
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

TEST(CalcTest, PressMinus)
{
    // FAIL();
    // 1. FAIL()을 통해 테스트를 명시적으로 실패할 수 있습니다.
    // 2. 실패의 원인을 함께 작성해주어야 합니다.
    FAIL() << "작성 중입니다.";
}
