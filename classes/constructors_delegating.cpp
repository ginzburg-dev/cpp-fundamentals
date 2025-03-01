#include <iostream>
#include <string>

class Ball
{
private:
    std::string m_color {};
    double m_radius{};

    void print() const
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
    }

public:
    // handles Ball(radius)
    Ball(double radius)
        : Ball( "black", radius )
    { 
        // we don't need to print() here since it will be called by the constructor we delegate to
    }

    Ball(std::string_view color = "black", double radius = 10.0)
        : m_color { color }
        , m_radius { radius }
    {  
        print();
    }
};

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty { 20.0 };
    Ball blueTwenty { "blue", 20.0 }; 

    return 0;
}
