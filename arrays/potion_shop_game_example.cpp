#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <cassert>
#include <limits>
#include <type_traits>
#include "../random/random.h"

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potions,
    };

    using namespace std::literals::string_view_literals;

    constexpr std::array types { healing, mana, speed, invisibility };
    constexpr std::array<int, max_potions> costs { 20, 30, 12, 50 };
    constexpr std::array<std::string_view, max_potions> names { "healing"sv, "mana"sv, "speed"sv, "invisibility"sv };

    static_assert(std::size(names) == max_potions);
    static_assert(std::size(costs) == max_potions);
    static_assert(std::size(types) == max_potions);
}

class Player
{
private:
    static constexpr int s_minStartingGold { 80 };
    static constexpr int s_maxStartingGold { 120 };

    std::string m_name{};
    int m_gold{};
    std::array<int,Potion::max_potions> m_inventory{ };

public:
    Player(std::string_view name)
        : m_name { name }, m_gold{ Random::get(s_minStartingGold, s_maxStartingGold) }
    {}

    int gold() const { return m_gold; }
    std::string_view name() const { return m_name; }
    int inventory(Potion::Type p) const { return m_inventory[p]; }
    bool buy(Potion::Type type)
    {
        if ( m_gold < Potion::costs[type] )
            return false;
        
        m_gold -= Potion::costs[type];
        ++m_inventory[type];
        return true;
    }

};

int charToInt(char c)
{
    return c - '0';
}


Potion::Type handleInput()
{
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char input{};
    while (true)
    {
        std::cin >> input;

        if (! std::cin )
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "That is an invalid input.  Try again: ";
            continue;
        }

        if ( !std::cin.eof() && std::cin.peek() != '\n' )
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }

        if ( charToInt(input) >= 0 && charToInt(input) < Potion::max_potions )
            return static_cast<Potion::Type>(charToInt(input));
        
        if ( input == 'q' )
            return Potion::max_potions;

        std::cout << "I didn't understand what you said.  Try again: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

void shop(Player& player)
{
    while (true)
    {
        std::cout << "Here is our selection for today: \n";
        for ( const auto& i : Potion::types)
        {
            std::cout << i << ") " << Potion::names[i] << " costs " << Potion::costs[i] << '\n';
        }
        std::cout << '\n';

        Potion::Type potion { handleInput() };
        if ( potion == Potion::max_potions )
            break;
    
        bool success { player.buy(potion) };
        if ( !success )
            std::cout << "You can not afford that.\n";
        else
            std::cout << "You purchased a potion of " <<  Potion::names[potion] << ".  You have " << player.gold() << " gold left.\n\n";
    }
}

void printInventory(Player& player)
{
    std::cout << "\nYour inventory contains:\n";

    for ( auto i : Potion::types )
        std::cout << player.inventory(i) << "x potion of " << Potion::names[i] << '\n';
    
    std::cout << "You escaped with " << player.gold() << " gold remaining.\n\n";
    
    std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";
}

int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\nEnter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    
    Player player{name};
    std::cout << "Hello, " << player.name() << ", you have " << player.gold() << " gold.\n\n";

    shop(player);

    printInventory(player);

    return 0;
}
