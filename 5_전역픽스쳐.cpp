// 5_전역픽스쳐.cpp
// => Test Fixture / Test Suite Fixture
//  : xUnit Test Framework의 공통적인 기능입니다.
// => Global Fixture
//  : Google Test 고유의 기능입니다.

// Global Test Fixture
//  : 프로그램의 시작/끝에서 픽스쳐를 설치하거나 해체하는 기능을 제공합니다.

#include <gtest/gtest.h>

TEST(ImageProcessorTest, ResizeImage) { }
TEST(SampleTest, foo) { }

// 전역 픽스쳐를 사용하는 방법
// 1) testing::Environment의 자식 클래스를 정의합니다.
class MyEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment.TearDown()" << std::endl;
    }
};

class MyEnvironment2 : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment2.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment2.TearDown()" << std::endl;
    }
};

// 2) 설치방법 2가지
//  => main 함수를 직접 정의할 때
//  => 여러 개의 전역 픽스쳐를 등록하는 경우, 반드시 main 함수를 직접 정의해서 사용하는 것이 안전합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::AddGlobalTestEnvironment(new MyEnvironment);
    testing::AddGlobalTestEnvironment(new MyEnvironment2);
    // 객체를 생성할 때는 반드시 new를 통해서 생성해야 합니다.

    return RUN_ALL_TESTS();
}

//  => main 함수를 라이브러리에 포함시켰을 때
//   : 전역 변수의 초기화가 main 함수 이전에 수행되는 특징을 이용합니다.
//    - C++ 표준에서 전역 변수의 초기화가 각 파일의 단위에서 어떤 순서로 초기화될 지 미정의 사항입니다.
// - test1.cpp
// testing::Environment* my_env1 = testing::AddGlobalTestEnvironment(new MyEnvironment);

// - test2.cpp
// testing::Environment* my_env2 = testing::AddGlobalTestEnvironment(new MyEnvironment);
