// 11_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
public:
    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "TearDown()" << std::endl;
    }

    static void SetUpTestSuite()
    {

        std::cout << "SetUpTestSuite()" << std::endl;
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite()" << std::endl;
    }
};

INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Range(0, 10));

//    testing::Test   <<WithParamInterface>> : GetParam()
//           |              |
//            --------------
//            |
//  testing::TestWithParam
//            |
//     ----------------------------
//     |                          |
// SampleTest_Sample_Test

// class SampleTest_Sample_Test : public SampleTest {
TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}

// * 구글 테스트에서 제공하는 테스트 케이스를 만드는 방법 3가지
// 1) TEST: 암묵적인 테스트 스위트 클래스

// 2) TEST_F: 명시적인 테스트 스위트 클래스
//     class SampleTest : public testing::Test {};
//     => 암묵적 설치/해체, 스위트 픽스쳐 설치/해체

// 3) TEST_P: 명시적인 테스트 스위트 클래스 + 파라미터화 테스트
//     class SampleTest : public testing::TestWithParam<InputType> {};
//     INSTANTIATE_TEST_SUITE_P(...)
//     => 암묵적 설치/해체, 스위트 픽스쳐 설치/해체
//     => GetParam()
