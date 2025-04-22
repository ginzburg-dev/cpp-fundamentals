#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0.0, double y=0.0, double z=0.0) 
        : m_x{ x }, m_y{ y }, m_z{ z } 
    {}

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }

    friend std::ostream& operator<<(std::ostream& out, const Point& point);
    friend std::istream& operator>>(std::istream& in, Point& point);
};

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";

    return out;
}

std::istream& operator>>(std::istream& in, Point& point)
{
    double x{};
    double y{};
    double z{};
    
    /*
    if (in >> x >> y >> z) // if all extractions succeeded
        point = Point{ x, y, z };
    */

    in >> x >> y >> z;
    if ( x < 0.0 || y < 0.0 || z < 0.0 )     // if any extractable input is negative
        in.setstate(std::ios_base::failbit); // set failure mode manually
    point = in ? Point{x, y, z} : Point{};

    return in;
}

int main()
{
    Point p1{ 1.2, 3.4 };
    Point p2{ 5.6, 7.8 };

    std::cout << p1 << ' ' << p2 << '\n';

    Point p3{};
    std::cout << "Enter a point: ";
    std::cin >> p3;

    std::cout << p3 << '\n';
    
    return 0;
}
