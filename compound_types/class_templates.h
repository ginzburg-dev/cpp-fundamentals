#ifndef CLASS_TEMPLATES_H
#define CLASS_TEMPLATES_H

#include <cmath>

template <typename T>
struct Point3d
{
    T x{};
    T y{};
    T z{};
};

template <typename T>
Point3d(T, T, T) -> Point3d<T>;

template <typename T>
constexpr auto length(const Point3d<T>& p) -> double
{
    return std::sqrt( p.x * p.x + p.y * p.y + p.z * p.z );
}

#endif
