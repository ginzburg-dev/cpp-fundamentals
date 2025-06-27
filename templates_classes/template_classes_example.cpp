#include <iostream>
#include <string>
#include <string_view>

template<typename T>
class Pair1
{
private:
    T m_first{};
    T m_second{};

public:
    Pair1(const T& first, const T& second)
        : m_first{first}, m_second{second}
    {}


    T& first() { return m_first; }
    T& second() { return m_second; }
    const T& first() const { return m_first; }
    const T& second() const { return m_second; }
};

template<typename T, typename S>
class Pair
{
private:
    T m_first{};
    S m_second{};

public:
    Pair(const T& first, const S& second)
        : m_first{first}, m_second{second}
    {}


    T& first() { return m_first; }
    S& second() { return m_second; }
    const T& first() const { return m_first; }
    const S& second() const { return m_second; }
};

template<typename S>
class StringValuePair : public Pair<std::string, S>
{
public:
    StringValuePair(std::string_view first, const S& second)
        : Pair<std::string, S>{static_cast<std::string>(first), second}
    {}
};

int main()
{
    Pair1<int> p1{ 5, 8 };
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2{ 2.3, 4.5 };
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    Pair<int, double> p3 { 5, 6.7 };
    std::cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
    
    const Pair<double, int> p4 { 2.3, 4 };
    std::cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    StringValuePair<int> svp{ "Hello", 5 };
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    
    return 0;
}
