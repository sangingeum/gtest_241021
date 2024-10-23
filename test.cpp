// test.cpp
#include <iostream>
using namespace std;

// 함수 오버로딩: 동일한 이름을 가지는 함수를, 인자 정보에 따라 여러개 제공할 수 있습니다.
// int square(int x) { return x * x; }
// double square(double x) { return x * x; }
// long long square(long long x) { return x * x; }

#if 0
template <typename T>
T square(T x) { return x * x; }

int main()
{
    std::cout << square(10) << std::endl;
    std::cout << square(3.14) << std::endl;
    std::cout << square(1000000000LL) << std::endl;
}
#endif

#if 0
class Rect {
public:
    void Draw() const { std::cout << "Rect Draw" << std::endl; }
};

class Circle {
public:
    void Draw() const { std::cout << "Circle Draw" << std::endl; }
};

// 인자로 Rect가 전달되면, Rect::Draw가 호출되고,
//    Circle이 전달되면, Circle::Draw가 호출되어야 합니다.
// 1) 가상 함수
void Draw()
{
}
#endif

#if 0
class Shape {
public:
    virtual void Draw() const = 0;
};

class Rect : public Shape {
public:
    void Draw() const override { std::cout << "Rect Draw" << std::endl; }
};

class Circle : public Shape {
public:
    void Draw() const override { std::cout << "Circle Draw" << std::endl; }
};

// 인자로 Rect가 전달되면, Rect::Draw가 호출되고,
//    Circle이 전달되면, Circle::Draw가 호출되어야 합니다.
// 1) 가상 함수
void Draw(Shape* p)
{
    p->Draw();
    // 동적 디스패치
    //  p가 참조하는 객체 타입이 Rect -> Rect::Draw
    //     참조하는 객체 타입이 Circle -> Circle::Draw
}

int main()
{
    Rect r;
    Draw(&r);

    Circle c;
    Draw(&c);
}
#endif

class Rect {
public:
    void Draw() const { std::cout << "Rect Draw" << std::endl; }
};

class Circle {
public:
    void Draw() const { std::cout << "Circle Draw" << std::endl; }
};

// 인자로 Rect가 전달되면, Rect::Draw가 호출되고,
//    Circle이 전달되면, Circle::Draw가 호출되어야 합니다.
// 1) 가상 함수
#if 0
void Draw(Rect* r)
{
    r->Draw();
}

void Draw(Circle* r)
{
    r->Draw();
}
#endif

template <typename T>
void Draw(T* r)
{
    r->Draw();
}

int main()
{
    Rect r;
    Draw(&r);

    Circle c;
    Draw(&c);
}
