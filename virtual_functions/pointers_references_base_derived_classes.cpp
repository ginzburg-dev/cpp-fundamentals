#include <iostream>
#include <array>
#include <string>
#include <string_view>

class Animal
{
protected:
    Animal(std::string_view name, std::string_view speak)
        : m_name{name}, m_speak{speak}
    {}

    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;

public:
    std::string_view getName() const { return m_name; }
    std::string_view speak() const { return m_speak; }

private:
    std::string m_name{};
    std::string m_speak{};
};

class Cat : public Animal
{
public:
    Cat(std::string_view name)
        : Animal{name, "Meow"}
    {}
};

class Dog : public Animal
{
public:
    Dog(std::string_view name)
        : Animal{name, "Woof"}
    {}
};

int main()
{
    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    const auto animals = std::to_array<const Animal*>( {&fred, &misty, &zeke, &garbo, &pooky, &truffle } ); // std::to_array creates a std::array from the one dimensional built-in array a[N]{}

    for (auto i : animals)
        std::cout << i->getName() << " says " << i->speak() << '\n';

    return 0;
}
