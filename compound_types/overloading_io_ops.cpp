#include <iostream>
#include <string_view>
#include <optional>

enum Pets
{
    parrot,
    fox,
    cow,
};

constexpr std::string_view getPetName(Pets pet)
{
    switch (pet)
    {
    case parrot: return "parrot";
    case fox: return "fox";
    case cow: return "cow";
    default: return "???";
    }
}

constexpr std::optional<Pets> getPetFromString(std::string_view sv)
{
    if (sv == "parrot") return parrot;
    if (sv == "fox") return fox;
    if (sv == "cow") return cow;

    return {};
}

std::ostream& operator<<(std::ostream& out, Pets pet)
{
    out << getPetName(pet);
    return out;
}

std::istream& operator>>(std::istream& in, Pets& pet)
{
    std::string s{};
    in >> s;

    std::optional<Pets> match { getPetFromString(s) };
    if (match)
    {
        pet = *match;
        return in;
    }

    in.setstate(std::ios_base::failbit);

    pet = {};

    return in;
}

std::string_view operator+(Pets pet1, Pets pet2)
{
    return "combination";
}

int main()
{
    Pets pet { fox };
    std::cout << pet << '\n';

    std::cout << Pets{ fox } + Pets{ cow } << '\n';

    std::cin >> pet;
    std::cout << pet << '\n';
    
    return 0;
}
