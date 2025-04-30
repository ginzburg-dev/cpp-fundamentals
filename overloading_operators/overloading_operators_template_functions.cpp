#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x=0, double y=0, double z=0)
        : m_x{x}, m_y{y}, m_z{z}
    {}

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    Point& operator+= (const Point& point);
    Point& operator/= (double x);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "<" << point.m_x << ", " << point.m_y << ", " << point.m_z << ">";
    return out;
}

Point& Point::operator+= (const Point& point)
{
    m_x += point.m_x;
    m_y += point.m_y;
    m_z += point.m_z;

    return *this;
}

Point& Point::operator/= (double x)
{
    m_x /= x;
    m_y /= x;
    m_z /= x;
    
    return *this;
}

template<typename T>
T average(const T* array, int nElements)
{
    T result{};
    
    for (int i{0}; i < nElements; ++i)
        result += array[i]; // we needed to override the '+=' operator here
    result /= nElements; // and the '/=' here

    return result;
}

int main()
{
    Point pArray[3]{ 
        Point{1.2, 3.4, 5.6},
        Point{0.4, 6.2, 2.9},
        Point{4.7, 0.6, 4.7}
    };

    Point pAverage{ average(pArray, std::size(pArray)) };

    std::cout << pAverage << '\n';

    return 0;
}
