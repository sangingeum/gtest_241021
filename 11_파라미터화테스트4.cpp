// 11_파라미터화테스트4.cpp

#include <gtest/gtest.h>

std::vector<std::string> LoadFromFile()
{
    // .. file 로드
    return {
        "Sonata",
        "Avante",
        "Genesis",
    };
}

std::string data[] = {
    "Sonata",
    "Avante",
    "Genesis",
};

class CarTest : public testing::TestWithParam<std::string> {
};

// * testing::ValuesIn을 사용하면,
//   함수 또는 컨테이너로부터 데이터 셋을 정의할 수 있습니다.
INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    // testing::ValuesIn(LoadFromFile()));
    testing::ValuesIn(data));

TEST_P(CarTest, foo)
{
    std::cout << GetParam() << std::endl;
}
