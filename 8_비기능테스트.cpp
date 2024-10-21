// 8_비기능테스트.cpp
#include <string>
#include <unistd.h>

// 비기능 테스트
// - 정의: 기능적으로 잘 동작할 뿐 아니라, 성능이나 메모리 등의 비기능적인 부분을 검증합니다.

// 아래 함수는 1초 이내로 수행되어야 합니다.
void Connect(const std::string& host)
{
    // ...
    sleep(2);
}

#include <gtest/gtest.h>

// 사용자 정의 단언문
#define EXPECT_TIMEOUT(fn, limit)                                                \
    do {                                                                         \
        time_t startTime = time(nullptr);                                        \
        fn;                                                                      \
        time_t duration = time(nullptr) - startTime;                             \
        EXPECT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과"; \
    } while (0)

// 아래 매크로 함수의 형태는 GNU 컴파일러에서만 지원합니다.
#define ASSERT_TIMEOUT(fn, limit)                                                \
    ({                                                                           \
        time_t startTime = time(nullptr);                                        \
        fn;                                                                      \
        time_t duration = time(nullptr) - startTime;                             \
        ASSERT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과"; \
    })

TEST(ConnecTest, Connect2)
{
    time_t limit = 1;
    EXPECT_TIMEOUT(Connect("https://server.com"), limit);
    ASSERT_TIMEOUT(Connect("https://server.com"), limit);
}

// 문제점
// : 일반적인 테스트의 구성과 다릅니다.
//   "가독성"
TEST(ConnecTest, Connect1)
{
    time_t limit = 1;

    //---
    time_t startTime = time(nullptr);
    Connect("https://server.com");
    time_t duration = time(nullptr) - startTime;
    //---

    EXPECT_LE(duration, limit) << "Timeout: " << limit << " second(s) 초과";
}
