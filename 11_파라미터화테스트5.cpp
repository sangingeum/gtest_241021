// 11_파라미터화테스트5.cpp
#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLUE,
    BLACK
};

int years[] = { 2022, 2023, 2024 };

std::vector<std::string> cars = {
    "Avante", "Sonata", "Genesis"
};

// 구글 테스트의 파라미터화 테스트는 두 개 이상의 데이터 셋을 조합해서
// 파라미터화 테스트를 수행할 수 있습니다.
// => testing::Combine
// => tuple

using CarType = std::tuple<std::string, Color, int>;

class CarTest : public testing::TestWithParam<CarType> { };

INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(Color::RED, Color::WHITE, Color::BLUE, Color::BLACK),
        testing::ValuesIn(years)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();

    std::string model = std::get<0>(data);
    Color color = std::get<1>(data);
    int year = std::get<2>(data);

    std::cout << model << ", " << color << ", " << year << std::endl;
}
