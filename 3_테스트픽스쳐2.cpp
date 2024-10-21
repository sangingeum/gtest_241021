// 3_테스트픽스쳐2.cpp
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

#define SPEC(msg) printf("[SPEC] %s\n", msg)

// 2. Test Fixture를 설치하는 방법
//  2) Delegate Set up(위임 설치)
// > 픽스쳐 설치에 관한 코드를 별도의 테스트 유틸리티 함수를 통해 캡슐화합니다.
//  => 명시적인 테스트 스위트 클래스를 제공해야 합니다.

//          testing::Test
//                 |
//              [CalcTest]
//                 |
//     --------------------------
//     |                         |
// CalcTest_PressPlus_Test   CalcTest_PressMinus_Test

// - 명시적인 테스트 스위트 클래스
class CalcTest : public testing::Test {
protected:
    Calc* CreateCalc() { return new Calc; }
};

// - 테스트 케이스를 만들 때, TEST_F를 이용해야 합니다.

// class CalcTest_PressPlus_Test : public CalcTest
TEST_F(CalcTest, PressPlus)
{
    SPEC("2 더하기 2를 하였을 때, 4의 결과가 나오는지 여부를 검증합니다.");
    // Arrange
    Calc* calc = CreateCalc();

    // Act
    calc->Enter(2);
    calc->PressPlus();
    calc->Enter(2);
    calc->PressEquals();

    // Assert
    // xUnit Test Framework은 다양한 단언문을 제공하고 있습니다.
    ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을 때";
}

// class CalcTest_PressMinus_Test : public CalcTest
TEST_F(CalcTest, PressMinus)
{
    Calc* calc = CreateCalc();

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(5);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 5) << "10 - 5를 하였을 때";
}

//          testing::Test
//                 |
//     --------------------------
//     |                         |
// CalcTest_PressPlus_Test   CalcTest_PressMinus_Test

//  class CalcTest_PressPlus_Test : public ::testing::Test

#if 0


//  class CalcTest_PressPlus_Test : public ::testing::Test
TEST(CalcTest, PressPlus)
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

// class CalcTest_PressMinus_Test : public ::testing::Test
TEST(CalcTest, PressMinus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(5);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 5) << "10 - 5를 하였을 때";
}
#endif
