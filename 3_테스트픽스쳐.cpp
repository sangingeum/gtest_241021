// 3_테스트픽스쳐.cpp
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

// 1. Test Fixture
// 정의: xUnit Test Framework 에서 SUT를 실행하기 위해 준비해야 하는 모든 것(사전 조건, 상태)을
//     "테스트 픽스쳐" 라고 합니다.
//     테스트 픽스쳐를 구성하는 모든 코드의 로직 부분을 "픽스쳐 설치(set up)"라고 합니다.

// 2. Test Fixture를 설치하는 방법
// 1) Inline Fixture Set up
//  : 모든 픽스쳐 설치를 테스트 케이스 안에서 수행합니다.
//  장점: 픽스쳐를 설치하는 과정과, 검증하는 로직이 하나의 테스트 케이스 안에서 나타나기 때문에
//      인과 관계를 분석하기 쉽다.
//  단점: 모든 테스트 케이스 안에서 "테스트 코드 중복"의 문제가 발생합니다.
//                          -------------
//                         테스트 냄새: 테스트의 가독성/유지보수성/신뢰성을 떨어뜨리는 요소

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
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(5);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 5) << "10 - 5를 하였을 때";
}
