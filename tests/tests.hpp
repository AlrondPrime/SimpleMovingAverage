#pragma once

#include "math.hpp"
#include "random.hpp"

#include <array>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

namespace tests
{
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

    void correctnessCheck()
    {
        // clang-format off
        const std::vector<math::Point<double>> dataset{
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
        const std::vector<math::Point<double>> resultDataset{
            {3, 34.333},
            {4, 34},
            {5, 36},
            {6, 35.333},
            {7, 37.333},
            {8, 36},
            {9, 37.333},
            {10, 36},
            {11, 37},
            {12, 34.667},
        };
        // clang-format on

        const auto result = math::sma(dataset, 3);
        std::cout << "Calculated values:\n" << to_string(result);

        assert(result.size() == resultDataset.size());
        for (size_t i{}; i < result.size(); ++i)
        {
            if (result[i] != resultDataset[i])
                assert(result[i] == resultDataset[i]);
        }
        std::cout << "predefined test passed" << std::endl;
    }

    namespace detail
    {
        template<typename T>
        void performanceCheck()
        {
            constexpr size_t datasetSize = 1'000'064;
            std::vector<math::Point<T>> dataset(datasetSize);
            for (size_t i{}; i < dataset.size(); ++i)
            {
                dataset[i].x = i;
                dataset[i].x = random::generateReal<T>();
            }

            const std::array<uint32_t, 6> desiredWindows{4, 8, 16, 32, 64, 128};

            // Measurement
            std::chrono::system_clock::time_point begin, end;
            std::map<uint32_t, double> measures;
            for (const auto &windowSize: desiredWindows)
            {
                measures.emplace(windowSize, 0);
            }

            constexpr uint32_t totalCounts = 1000;
            double secondsElapsed;
            for (size_t i{}; i < totalCounts; ++i)
            {
                for (auto &[windowSize, measure]: measures)
                {
                    begin = std::chrono::system_clock::now();
                    const auto result = math::sma(dataset, windowSize);
                    end = std::chrono::system_clock::now();
                    // we measure in Points/second
                    secondsElapsed =
                        std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
                        / 1'000'000'000.0;
                    measure += result.size() / secondsElapsed;
                }
            }

            for (auto &[windowSize, measure]: measures)
            {
                measure /= totalCounts;
                std::cout << "for window size " << windowSize << " we measured " << measure
                      << " Points/second" << std::endl;
            }


        }
    } // namespace detail

    void performanceCheck()
    {
        std::cout << "measure performance for 'float' type" << std::endl;
        detail::performanceCheck<float>();
        std::cout << "measure performance for 'double' type" << std::endl;
        detail::performanceCheck<double>();

        std::cout << "performance test finished" << std::endl;
    }
} // namespace tests