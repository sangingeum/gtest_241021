// 8_비기능테스트2.cpp
#include <iostream>
#include <string>

// Sanitizer
// => 대부분의 최신 컴파일러가 제공되는 도구 입니다.
//    - 메모리 / 스레드 / 미정의 동작
// => 모든 플랫폼에서 제공되지는 않습니다.
//    - 컴파일 옵션: -fsanitize=address
//                -fsanitize=thread
//                -fsanitize=undefined

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
};

bool DrawImage(const std::string& url)
{
    Image* p = new Image { url };
    Image* p2 = new Image { url };
    p->Draw();

    delete p;

    return true;
}

#include <gtest/gtest.h>

TEST(ImageTest, DrawImage)
{
    bool result = DrawImage("https://a.com/a.jpeg");
    EXPECT_TRUE(result);
}
