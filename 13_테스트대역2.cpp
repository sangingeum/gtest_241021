// 13_테스트대역2.cpp
#include <string>

// * 테스트 대역
// - 목적: 테스트 환경을 통제하기 위해서 사용합니다.
// - 적용: 테스트 대역을 적용하기 위해서는 제품 코드(SUT)가 테스트 대역을 적용할 수 있는 설계가
//        필요합니다.
//      "약한 결합 / 느슨한 결합"
//    : 협력 객체를 이용할 때, 추상 타입(추상 클래스 / 인터페이스)에 의존하는 것

// Logger
//   IsValidLogFilename  -----<> <<IFileSystem>>
//                                      |
//                                    --------
//                                   |       |
//                             FileSystem  [TestDouble]

// 1) 협력 객체의 인터페이스
class IFileSystem {
public:
    virtual ~IFileSystem() { }
    virtual bool IsValidFilename(const std::string& name) = 0;
};

// 2) 협력 객체는 협력 객체의 인터페이스를 구현해야 합니다.
class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& name) override
    {
        // 현재의 파일 시스템에서 생성 가능한 이름인지 확인합니다.
        //  : Ext3, Ext4, NTFS, FAT ...
        // return true;
        return false;
    }
};

// 3) 핵심: 협력 객체를 직접 생성하는 것이 아니라, 외부에서 생성해서 전달해야 합니다.
//        직접 생성하면 강한 결합이 형성됩니다.
//       "의존성 주입(Dependency Injection, DI)"
//        1) 생성자 주입
//          : 협력 객체가 필수적일 때
//        2) 메소드 주입
//          : 협력 객체가 필수적이지 않을 때

class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p)
        : fs { p }
    {
    }

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

        // FileSystem fs;
        // return fs.IsValidFilename(filename);

        // IFileSystem* fs = new FileSystem;
        return fs->IsValidFilename(filename);
    }
};

#include <gtest/gtest.h>

// 테스트 대역은 협력 객체의 인터페이스를 구현하면 됩니다.
class TestDouble : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        return true;
    }
};

TEST(LoggerTest, IsValidLogFilename_NameLongerThan5Chars_ReturnsTrue)
{
    TestDouble fs;
    Logger logger { &fs };
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 5글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_ShorterThan5Chars_ReturnsFalse)
{
    TestDouble fs;
    Logger logger { &fs };
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 5글자 미만일 때";
}

//-------
#include <gmock/gmock.h>

class MockFileSystem : public IFileSystem {
public:
    // bool IsValidFilename(const std::string& filename) override
    MOCK_METHOD(bool, IsValidFilename, (const std::string& filename), (override));
};

using testing::NiceMock;
using testing::Return;

TEST(LoggerTestGoogleMock, IsValidLogFilename_NameLongerThan5Chars_ReturnsTrue)
{
    std::string validFilename = "valid.log";
    NiceMock<MockFileSystem> fs;
    ON_CALL(fs, IsValidFilename(validFilename)).WillByDefault(Return(true));
    Logger logger { &fs };

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 5글자 이상일 때";
}

TEST(LoggerTestGoogleMock, IsValidLogFilename_ShorterThan5Chars_ReturnsFalse)
{
    std::string invalidFilename = "bad.log";
    NiceMock<MockFileSystem> fs;
    ON_CALL(fs, IsValidFilename(invalidFilename)).WillByDefault(Return(true));
    Logger logger { &fs };

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 5글자 미만일 때";
}

// * 테스트 대역(Test Double)
// : xUnit Test Pattern
// => 4가지 종류
// 1) Test Stub
// 2) Fake Object
// 3) Test Spy
// 4) Mock Object
