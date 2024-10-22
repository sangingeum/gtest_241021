// 17_Mock.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR,
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

// 파일에 로그를 기록합니다.
class FileTarget : public DLoggerTarget { };

// 로그를 네트워크로 전송합니다.
class NetworkTarget : public DLoggerTarget { };

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
        }
    }
};

// * 문제점
// : DLogger의 Write를 수행하였을 때,
//   검증할 수 있는 상태가 존재하지 않습니다.

// * Mock Object Pattern
// 의도: SUT의 함수를 호출하였을 때, 발생하는 부수 효과를 관찰할 수 없어서
//     테스트되지 않은 요구사항이 존재합니다.
// 방법: "행위 기반 검증"을 수행합니다.

// - 상태 검증
//  : SUT에 작용을 가한후, 내부 상태 변화를 단언문을 통해 확인합니다.
// - 동작 검증
//  : SUT에 작용을 가한후, 협력 객체를 대상으로 내부적으로 발생하는 함수의 호출 여부, 호출 인자, 호출 횟수,
//    호출 순서 등의 정보를 통해 정상 동작 여부를 판단합니다.
//  => Mock Framework를 통해서, 모의 객체를 쉽게 만들 수 있습니다.

// C++ Mock Framework
//  => Google Mock Framework 입니다.
//  => Google Test 1.8 이후로, Google Mock 프로젝트가 흡수되었습니다.

#include <gmock/gmock.h>
// 위의 헤더를 통해 gtest/gtest.h도 포함되기 때문에, 별도로 포함할 필요가 없습니다.

class MockDLoggerTarget : public DLoggerTarget {
public:
    // virtual void Write(Level level, const std::string& message)
    // Mocking => MOCK_METHOD 매크로를 이용하면 됩니다.

    // MOCK_METHOD{인자개수}(메소드 이름, 메소드 타입)
    MOCK_METHOD2(Write, void(Level level, const std::string& message));
};
