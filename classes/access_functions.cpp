#include <iostream>

/*
1. If your class has no invariants and requires a lot of access functions, 
consider using a struct (whose data members are public) and providing direct access to members instead.
2. Prefer implementing behaviors or actions instead of access functions. For example, instead of a setAlive(bool) setter, 
implement a kill() and a revive() function. 
3. Only provide access functions in cases where the public would reasonably need to get or set the value of an individual member.
*/

class Point3d
{
private:
    double m_x { 0 };
    double m_y { 0 };
    double m_z { 0 };

public:
    void print() const
    {
        std::cout << '<' << m_x << ", " << m_y << ", " << m_z << ">\n";
    }

    double getX() const { return m_x; }
    void setX(double x) { m_x = x; }

    double getY() const { return m_y; }
    void setY(double y) { m_y = y; }

    double getZ() const { return m_z; }
    void setZ(double z) { m_z = z; }

    void set(double x, double y, double z) { m_x = x; m_y = y; m_z = z; }
};

int main()
{
    Point3d p1{};
    p1.set(1.2, 3.4, 5.6);

    p1.print();
    std::cout << "X: " << p1.getX() << "\n";
    std::cout << "Y: " << p1.getY() << "\n";
    std::cout << "Z: " << p1.getZ() << "\n";

    return 0;
}
