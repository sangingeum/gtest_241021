// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
protected:
    ImageProcessorTest()
    {
        std::cout << "ImageProcessorTest()" << std::endl;
    }

    ~ImageProcessorTest()
    {
        std::cout << "~ImageProcessorTest()" << std::endl;
    }

    void SetUp() override
    {
        std::cout << "SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "TearDown()" << std::endl;
    }
};

// * 암묵적 설치/해체를 위해서는 테스트 케이스를 TEST_F를 통해서 구성해야 합니다.
TEST_F(ImageProcessorTest, ResizeImage) { }
TEST_F(ImageProcessorTest, BlurImage) { }

// Test Runner가 테스트케이스를 수행하는 흐름
// => 신선한 픽스쳐 전략
// : 각 테스트 케이스마다 새로운 픽스쳐 객체를 생성하고 파괴하는 형태로 테스트 케이스가 수행됩니다.
//  - 픽스쳐의 상태가 이전의 테스트로 인해 망가지더라도, 영향을 받지 않습니다.

// ImageProcessorTest 객체 생성
//   .SetUp()
//    테스트 수행(ResizeImage)
//   .TearDown()
// ImageProcessorTest 객체 파괴

// ImageProcessorTest 객체 생성
//   .SetUp()
//    테스트 수행(BlurImage)
//   .TearDown()
// ImageProcessorTest 객체 파괴
