#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
public:
    Point(double x, double y)
    {
        std::cout << "Point(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Point p{ 2.3, 4.5 };
    p.print();

    return 0;
}
