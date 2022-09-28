#ifndef UTILITY_H
#define UTILITY_H

#include <array>

template<typename>
struct ArrSize;

template<typename T, std::size_t TN>
struct ArrSize<const std::array<T,TN> >
{
    static std::size_t const size = TN;
};

template<typename T, std::size_t TN>
struct ArrSize<std::array<T,TN> >
{
    static std::size_t const size = TN;
};

#endif // UTILITY_H
