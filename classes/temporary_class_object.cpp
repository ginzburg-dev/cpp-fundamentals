#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair() = default;
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

IntPair returnFunc1()
{
    return IntPair{ 1, 2 }; // returns temporary object 
}

IntPair returnFunc2()
{
    return { 1, 2 }; // Implicitly convert { 1, 2 } into IntPair{ 1, 2 } (initialized using another temporary object)
}

int main()
{
    IntPair p { 3, 4 };
    print(p); // Pass variable

    print( IntPair{5, 6} ); // Construct temporary IntPair and pass to a function

    print( { 7, 8 } ); // Implicitly convert { 7, 8 } to a temporary object IntPait and pass to a function. Deduce from function parameter

    IntPair{ 7, 8 }; // Temporary object IntPair
    IntPair(p1); // Defines a variable p1

    char c { 'a' };
    
    std::cout << static_cast<int>( c ) << '\n'; // static_cast returns a temporary int direct-initialized with value of c
    std::cout << int { c } << '\n';             // explicitly creates a temporary int list-initialized with value c


    return 0;
}
