#include <iostream>

// Prefer the implicit copy constructor, unless you have a specific reason to create your own.

class Point
{
private:
    int m_x { 0 };
    int m_y { 0 };

public:
    Point(int x = 0, int y = 0) // Default constructor
        : m_x { x }, m_y { y }
    {
    }

    Point(const Point& point) // Copy constructor
        : m_x { point.m_x }
        , m_y { point.m_y }
    {
        std::cout << "Copy constructor called\n";
    }

    /*
    Point(const Point& point) = default; // Explicitly request default copy constructor
    Point(const Point& point) = delete; // Delete the copy constructor so no copies can be made
    */
    void print() const
    {
        std::cout << "<" << m_x << ", " << m_y << ">\n";
    }
};

void printPoint(Point point) // passing by value using copy constructor
{
    point.print();
}

Point generatePoint(int x, int y)
{
    Point p { x, y };
    return p; // Generated temporary object by invoking copy constructor
}

int main()
{
    Point p1 { 1, 2 };
    Point p2 { p1 }; // Call a copy constructor 

    p1.print();
    p2.print();

    printPoint(p1); // p1 is copied into the function parameter using copy constructor

    Point p3 { generatePoint(2, 3) }; // Point is returned using copy constructor
    printPoint(p3);
    
    return 0;
}
