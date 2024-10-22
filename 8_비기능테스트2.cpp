// 8_비기능테스트2.cpp
#include <iostream>
#include <string>

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url { s }
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image : " << url << std::endl;
    }

#ifdef GTEST_LEAK_TEST
    static int allocCount;

    void* operator new(size_t size)
    {
        ++allocCount;
        return malloc(size);
    }

    void operator delete(void* p, size_t)
    {
        free(p);
        --allocCount;
    }
#endif
};

// new
// 1) 메모리 할당 => operator new
// 2) 생성자 호출

// delete
// 1) 소멸자 호출
// 2) 메모리 해지 => operator delete

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

bool DrawImage(const std::string& url)
{
    Image* p = new Image { url };
    Image* p2 = new Image { url };
    p->Draw();

    // ...

    return true;
}

#include <gtest/gtest.h>

// 메모리의 누수 여부를 단위 테스트를 통해서 검증하고 싶습니다.
//  * SUT의 클래스에 메모리 관련 함수를 재정의합니다.
//    operator new
//    operator delete

#if 0
TEST(ImageTest, DrawImage)
{
    int allocCount = Image::allocCount;
    DrawImage("https://a.com/a.jpeg");
    int diff = Image::allocCount - allocCount;

    EXPECT_EQ(diff, 0) << "memory leaks: " << diff << " object(s) leak!";
}
#endif

class ImageTest : public testing::Test {
protected:
    int allocCount = 0;
    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        allocCount = Image::allocCount;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::allocCount - allocCount;
        EXPECT_EQ(diff, 0) << "memory leaks: " << diff << " object(s) leak!";
#endif
    }
};

TEST_F(ImageTest, DrawImage)
{
    bool result = DrawImage("https://a.com/a.jpeg");
    EXPECT_TRUE(result);
}
