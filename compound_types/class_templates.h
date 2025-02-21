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
constexpr auto length(Point3d<T> p) -> double
{
    return std::sqrt( p.x * p.x + p.y * p.y + p.z * p.z );
}

#endif
