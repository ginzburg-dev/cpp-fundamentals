#include "Point3.h"
#include <iostream>

Point3::Point3(double x, double y, double z)
    : m_x { x }
    , m_y { y }
    , m_z { z }
{
}

void Point3::print() const
{
    std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
}
