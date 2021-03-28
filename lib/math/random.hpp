#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <random> // std::mt19937
#include <functional> // std::bind

template <typename T>
inline auto getEngine(
    const T &min = std::numeric_limits<T>::min(),
    const T &max = std::numeric_limits<T>::max())
{

    std::mt19937 twister{std::random_device{}()};

    if constexpr (std::is_integral<T>::value)
        return std::bind(std::uniform_int_distribution<T>(min, max), twister);
    else
        return std::bind(std::uniform_real_distribution<T>(min, max), twister);

}

#endif