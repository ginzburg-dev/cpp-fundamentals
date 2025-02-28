#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x = 10, int y = 10) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }

    friend void print(const Foo& foo);
};

class Boo
{
private:
    int m_u{};
    int m_v{};

public:
    //Boo() // default constructor like this less preferable
    //{
    //}

    Boo() = default; // prefer this as a default constructor over a default constructor with an empty body

    Boo(int u, int v) // Boo(int u = 0, int v = 0) it shouldn't be used with default args since Boo is overloaded and already has a default constructor, thus causing ambiguous constructor call. see Delegate
        : m_u { u }
        , m_v { v }
    {
        std::cout << "Boo(" << m_u << ", " << m_v << ") constructed\n";
    }

    friend void print(const Boo& boo);
};

void print(const Foo& foo)
{
    std::cout << "xy: <" << foo.m_x << ", " << foo.m_y << ">\n";
}

void print(const Boo& boo)
{
    std::cout << "uv: <" << boo.m_u << ", " << boo.m_v << ">\n";
}

int main()
{
    Foo foo1{};
    Foo foo2{ 6, 7 };

    print(foo1);
    print(foo2);

    Boo boo1{};
    Boo boo2{ 8, 9 };

    print(boo1);
    print(boo2);

    return 0;
}
