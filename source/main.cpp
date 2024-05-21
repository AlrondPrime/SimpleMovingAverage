#include <cassert>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "math.hpp"

template<typename T>
std::string to_string(const std::vector<math::Point<T>> &vec)
{
    std::ostringstream os;
    os << std::fixed;
    os << std::setprecision(3);
    for (const auto &p: vec)
    {
        os << "x:" << p.x << ", y:" << p.y << "\n";
    }
    return os.str();
}

int main()
{
    // clang-format off
    std::vector<math::Point<double>> dataset{
        {1, 34},
        {2, 32},
        {3, 37},
        {4, 33},
        {5, 38},
        {6, 35},
        {7, 39},
        {8, 34},
        {9, 39},
        {10, 35},
        {11, 37},
        {12, 32},
    };
    // clang-format on

    const auto result = math::sma(dataset, 3);
    std::cout << to_string(result) << std::endl;

    return EXIT_SUCCESS;
}
