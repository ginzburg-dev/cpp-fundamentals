#include <iostream>

class Date
{

public:

    void print() const
    {
        std::cout << '[' << m_day << '/' << m_month << '/' << m_year << "]\n"; 
    }

private:

    int m_day { 14 };
    int m_month { 01 };
    int m_year { 2021 };

};

class Vector3
{
private:
    double m_x {};
    double m_y {};
    double m_z {};

public:
    void set(double x, double y, double z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    void set(const Vector3& v) // member function can also directly access the private members of ANY other object of the same class type that is in scope
    {
        m_x = v.m_x;
        m_y = v.m_y;
        m_z = v.m_z;
    }

    bool isEqual(const Vector3& v) const
    {
        return ( m_x == v.m_x )&&( m_y == v.m_y )&&( m_z == v.m_z );
    }

    void print() const
    {
        std::cout << '<' << m_x << ", " << m_y << ", " << m_z << ">\n"; 
    }
};

int main()
{
    Date date {};
    date.print();

    Vector3 v1{};
    v1.set(1,2,3);

    Vector3 v2{};
    v2.set(v1);

    v2.print();

    v2.set(2, 3, 4);

    std::cout << v1.isEqual(v2) << '\n';

    return 0;
}
