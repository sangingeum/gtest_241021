// 10_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    virtual void Start() // 가상함수!
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine { p }
    {
    }

    void Go() const
    {
        // ...
        engine->Start();
        // ...
    }
};

#include <gtest/gtest.h>

// Car의 Go가 호출되면, Engine이 Start 되었을 것이다.
// * 문제점
// : Engine이 Start 되었을 때, Engine 객체를 통해 확인할 수 있는 기능이 제공되지 않아서
//   단언문을 작성할 수 없습니다.

// * 가상함수!
//  - 테스트 전용 하위 클래스를 만들어서, 호출을 후킹할 수 있습니다.
class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        std::cout << "TestEngine Start" << std::endl;
        Engine::Start();
        isStart = true; // !!!!
    }

    // 테스트에서 확인할 수 있는 기능을 테스트 전용 하위 클래스를 통해 제공합니다.
    bool IsStart() const
    {
        return isStart;
    }
};

TEST(CarTest, Go)
{
    // Engine engine;
    TestEngine engine;
    Car car { &engine };

    car.Go();

    EXPECT_TRUE(engine.IsStart()) << "자동차가 Go 하였을 때";
}
