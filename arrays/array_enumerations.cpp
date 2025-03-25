#include <iostream>
#include <array>
#include <cassert>
#include <string>
#include <string_view>

namespace Animal
{
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals,
    };

    struct Data
    {
        std::string_view name{};
        int legs{};
        std::string_view sound{};
    };

    using namespace std::literals::string_view_literals;

    constexpr std::array animals {
        Data{ "chicken"sv, 2, "cluck"sv },
        Data{ "dog"sv, 2, "woof"sv },
        Data{ "cat"sv, 2, "meow"sv },
        Data{ "elephant"sv, 2, "pawoo"sv },
        Data{ "duck"sv, 2, "quack"sv },
        Data{ "snake"sv, 2, "hissss"sv },
    };

    static_assert( std::size(animals) == Type::max_animals ); 
}

std::istream& operator>>(std::istream& in, Animal::Type& animal)
{
    std::string input {};
    std::getline(in >> std::ws, input );

    for ( std::size_t index{0}; index < Animal::animals.size(); ++index )
    {
        if ( Animal::animals[index].name == input )
        {
            animal = static_cast<Animal::Type>(index);
            return in;
        }
    }

    in.setstate(std::ios_base::failbit); // mark as failed bit to catch if the animal's name didn't match
    return in;
}

std::ostream& operator<<(std::ostream& out, const Animal::Data& animal)
{
    out << "A " << animal.name << " has " << animal.legs << " legs and says " << animal.sound;
    return out;
}

int main()
{
    std::cout << "Enter an animal name: ";
    Animal::Type input{};
    std::cin >> input;

    if (!std::cin)
    {
        std::cin.clear();
        std::cout << "The animal couldn't be found\n";
        input = Animal::max_animals; // set to invalid option so we don't match below
    } 
    else
        std::cout << Animal::animals[input] << '\n';

    return 0;
}
