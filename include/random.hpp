#pragma once

#include <random>

namespace random
{
    /**
     * @brief Generate random real value
     * @tparam T floating point type
     * @return generated random value
     */
    template<typename T>
    T generateReal()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<T> dist(std::numeric_limits<T>::min(),
                                                      std::numeric_limits<T>::max());

        return dist(gen);
    }
} // namespace random
