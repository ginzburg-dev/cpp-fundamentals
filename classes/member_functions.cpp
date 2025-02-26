#include <iostream>
#include <string>
#include <string_view>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << day << '/' << month << '/' << year << '\n';
    }
};

struct Vector3d
{
    double x {};
    double y {};
    double z {};

    void add(const Vector3d& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    void print()
    {
        std::cout << '[' << x << ", " << y << ", " << z << "]\n";
    }

    void print(std::string_view prefix)
    {
        std::cout << prefix << '[' << x << ", " << y << ", " << z << "]\n";
    }
};

int main()
{
    Date today { 2025, 02, 25 };

    today.day = 26;
    today.print();

    Vector3d v1 { 1.0, 2.0, 3.0 };
    Vector3d v2 { 4.0, 5.0, 6.0 };

    v1.add(v2);
    v1.print();
    v2.print("Vector 2: ");
    
    return 0;
}
