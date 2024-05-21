#pragma once

#include <cmath>
#include <cstdint>
#include <vector>
#include <stdexcept>

namespace math
{
    // Constants
    constexpr uint32_t gDesiredPrecision = 3; // digits after point

    /**
     * @tparam T floating point type
     * @param v value to round
     * @param desiredPrecision how many significant digits should be left after the point
     * @return rounded value
     */
    template<typename T>
    double round(T v, uint32_t desiredPrecision = gDesiredPrecision)
    {
        return std::round(v * std::pow(10, desiredPrecision)) / std::pow(10, desiredPrecision);
    }

    template<typename T>
    struct Point {
        using value_t = T;
        T x{}, y{};
    };

    template<typename T>
    bool operator==(const Point<T> &left, const Point<T> &right)
    {
        return round(left.x) == round(right.x) && round(left.y) == round(right.y);
    }

    template<typename T>
    bool operator!=(const Point<T> &left, const Point<T> &right)
    {
        return !(left==right);
    }

    /**
     * @brief count simple moving average
     * @details https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
     */
    template<typename T>
    std::vector<Point<T>>
    sma(const std::vector<Point<T>> &coordinates, const uint32_t windowSize)
    {
        if(coordinates.size() < windowSize)
            throw std::logic_error{"window size less than dataset size"};

        std::vector<Point<T>> averages;
        averages.reserve(coordinates.size() / windowSize);
        typename Point<T>::value_t average;

        // Count first SMA
        average = 0;
        for (size_t i{}; i < windowSize; ++i)
        {
            average += coordinates[i].y;
        }
        average /= windowSize;
        averages.emplace_back(Point<T>{coordinates[windowSize - 1].x, average});

        // Count remaining SMAs using previous counted value
        for (size_t i{1}; i < coordinates.size() - windowSize + 1; ++i)
        {
            average = averages.back().y - coordinates[i - 1].y / windowSize
                    + coordinates[i + windowSize - 1].y / windowSize;
            averages.emplace_back(Point<T>{coordinates[i + windowSize - 1].x, average});
        }

        return averages;
    }

} // namespace math
