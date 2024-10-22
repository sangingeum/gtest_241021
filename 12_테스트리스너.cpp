// 12_테스트리스너.cpp
// => Google Test Framework 고유의 기능입니다.
// : 모든 테스트의 과정에서 수행해야 하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, foo) { }

TEST(ImageProcessorTest, foo) { }

// 1) 리스너 정의
// => testing::TestEventListener
//    testing::EmptyTestEventListener

using testing::TestSuite;
using testing::UnitTest;

class TestListener : public testing::EmptyTestEventListener {
public:
    void OnEnvironmentsSetUpStart(const UnitTest& /*unit_test*/) override
    {
        std::cout << "OnEnvironmentsSetUpStart" << std::endl;
    }
    void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/) override
    {
        std::cout << "OnEnvironmentsSetUpEnd" << std::endl;
    }

    void OnEnvironmentsTearDownStart(const UnitTest& /*unit_test*/) override
    {
        std::cout << "OnEnvironmentsTearDownStart" << std::endl;
    }

    void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/) override
    {
        std::cout << "OnEnvironmentsTearDownEnd" << std::endl;
    }

    void OnTestSuiteStart(const TestSuite& /*test_suite*/) override
    {
        std::cout << "OnTestSuiteStart" << std::endl;
    }

    void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override
    {
        std::cout << "OnTestSuiteEnd" << std::endl;
    }
};

// 2) 리스너 등록
// => main 함수를 직접 정의해서 등록해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    // 1. 리스너 관리 객체를 얻습니다.
    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();

    // 2. 리스너를 등록합니다.
    listeners.Append(new TestListener);

    return RUN_ALL_TESTS();
}
