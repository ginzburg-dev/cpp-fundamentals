#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

class Car
{
private:
    std::string_view m_make{};
    std::string_view m_model{};

public:
    Car(std::string_view make, std::string_view model)
        : m_make{ make }, m_model{ model }
    {}

    friend bool operator<(const Car& c1, const Car& c2) { return c1.m_make[0] < c2.m_make[0]; }
    friend bool operator>(const Car& c1, const Car& c2) { return c2 < c1; }
    
    friend bool operator==(const Car& c1, const Car& c2)  { return c1.m_make[0] == c2.m_make[0]; }
    friend bool operator!=(const Car& c1, const Car& c2)  { return c1.m_make[0] != c2.m_make[0]; }

    friend bool operator<=(const Car& c1, const Car& c2)  { return !(c1 > c2); }
    friend bool operator>=(const Car& c1, const Car& c2)  { return !(operator<(c1, c2)); }

    friend std::ostream& operator<<(std::ostream& out, const Car& car);
};

std::ostream& operator<<(std::ostream& out, const Car& car)
{
    out << "(" << car.m_make << ", " << car.m_model << ")";
    return out;
}

int main()
{
    // Example 1
    Car c1 { "A", "a" };
    Car c2 { "B", "b" };
    std::cout << (c1 < c2) << ' ' << (c1 > c2) << ' ' << ( c1 != c2 ) << '\n';

    // Example 2
    std::vector<Car> cars {
        { "Toyota", "Corolla" },
        { "Honda", "Accord" },
        { "Toyota", "Camry" },
        { "Honda", "Civic" }
    };

    std::sort(cars.begin(), cars.end()); // Overloading of the '<' operator is required

    for (const auto& c : cars )
        std::cout << c << '\n';

    return 0;
}
