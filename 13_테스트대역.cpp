// 13_테스트대역.cpp
#include <string>

class FileSystem {
public:
    bool IsValidFilename(const std::string& name)
    {
        // 현재의 파일 시스템에서 생성 가능한 이름인지 확인합니다.
        //  : Ext3, Ext4, NTFS, FAT ...
        // return true;
        return false;
    }
};

class Logger {
public:
    // 파일의 확장자를 제외한 파일명이 5글자 이상이어야 한다.
    // ex)
    //  file.log => file  => X
    // hello.log => hello => O
    bool IsValidLogFilename(const std::string& filename)
    {
        //----- 테스트 대상 코드 영역 시작
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //----- 테스트 대상 코드 영역 끝

        FileSystem fs;
        return fs.IsValidFilename(filename);
    }
};

// Logger
//   IsValidLogFilename ---> FileSystem
//                               IsValidFilename

// Logger
//   IsValidLogFilename ---> TestDouble
//                               IsValidFilename

// * 테스트 대역
// - 목적: 테스트 환경을 통제하기 위해서 사용합니다.
// - 적용: 테스트 대역을 적용하기 위해서는 제품 코드(SUT)가 테스트 대역을 적용할 수 있는 설계가
//        필요합니다.
//      "약한 결합 / 느슨한 결합"

#include <gtest/gtest.h>

// * 문제점
//  : 단위 테스트의 결과가 테스트 대상 코드 영역에 의해서만 결정되는 것이 아니라,
//    협력 객체에 의해서 변경될 수 있습니다.

TEST(LoggerTest, IsValidLogFilename_NameLongerThan5Chars_ReturnsTrue)
{
    Logger logger;
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 5글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_ShorterThan5Chars_ReturnsFalse)
{
    Logger logger;
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 5글자 미만일 때";
}

// * 테스트 코드에서 전달되는 인자나 변수명을 지을 때, 테스트의 의도가 표현될 수 있도록 만드는 것은
//   테스트 코드의 가독성에 도움이 됩니다.
