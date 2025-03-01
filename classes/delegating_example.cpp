#include <iostream>

class Point
{
private:
    int m_x{ 0 };
    int m_y{ 0 };

public:
    Point() = default;

    Point(int x, int y)
        : m_x { x }
        , m_y { y }
    {
    }

    Point(int i)
        : Point(i, i)
    {
    }

    void print() const
    {
        std::cout << "Point<" << m_x << ", " << m_y << ">\n";
    }
};

int main()
{
    Point p1{};
    p1.print();

    Point p2{100};
    p2.print();

    Point p3{200, 300};
    p3.print();

    return 0;
}
