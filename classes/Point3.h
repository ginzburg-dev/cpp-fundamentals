#ifndef POINT3_H
#define POINT3_H

class Point3
{
private:
    double m_x { 0.0 };
    double m_y { 0.0 };
    double m_z { 0.0 };

public:
    Point3() = default;
    Point3(double x, double y, double z);

    void print() const;

    double x() const { return m_x; } // it's ok to define a one-lined (trivial) function in the class body
    double y() const { return m_y; }
    double z() const { return m_z; }
};

#endif
