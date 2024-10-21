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
};

int Image::allocCount = 0;

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
TEST(ImageTest, DrawImage)
{
    int allocCount = Image::allocCount;
    DrawImage("https://a.com/a.jpeg");
    int diff = Image::allocCount - allocCount;

    EXPECT_EQ(diff, 0) << "memory leaks: " << diff << " object(s) leak!";
}
