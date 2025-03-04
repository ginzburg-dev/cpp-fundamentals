#ifndef POINT2_H
#define POINT2_H

#include <cmath>
#include <iostream>

class Point2
{
private:
    double m_x { 0.0 };
    double m_y { 0.0 };

public:
    Point2() = default;
    Point2(double x, double y);

    void print() const { std::cout << '<' << m_x << ", " << m_y << ">\n"; } // implicitly 'inline' because it defined inside the class body

    //double Length(const Point2& p) const;

    void set(double x = 0, double y = 0); // preferr putting default arguments here

    double x() const { return m_x; } // inline
    double y() const { return m_y; } // inline

    friend double Length(const Point2& p1, const Point2& p2);
};

inline double Length(const Point2& p1, const Point2& p2) // make it inline
{
    return std::sqrt( (p1.m_x - p2.m_x)*(p1.m_x - p2.m_x) + (p1.m_y - p2.m_y)*(p1.m_y - p2.m_y) );
}

inline Point2::Point2(double x, double y) // now inline
    : m_x { x }, m_y { y }
{
}

inline void Point2::set(double x, double y) // now inline. default arguments were put in the class declaration
{
    m_x = x;
    m_y = y;
}

#endif
