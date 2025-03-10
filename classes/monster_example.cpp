#include "../random/random.h"
#include <iostream>
#include <string>
#include <string_view>

class Monster
{
public:
    enum Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        maxMonsterTypes,
    };

private:
    Type m_type {};
    std::string m_name { "???" };
    std::string m_roar { "???" };
    int m_hit {};

public:
    Monster(Type type, std::string_view name, std::string_view roar, int hit)
        : m_type { type }, m_name { name }, m_roar { roar }, m_hit { hit }
    {
    }

    constexpr std::string_view getTypeName() const
    {
        switch(m_type)
        {
        case Monster::dragon: return "Dragon";
        case Monster::goblin: return "Goblin";
        case Monster::ogre: return "Ogre";
        case Monster::orc: return "Orc";
        case Monster::skeleton: return "Sceleton";
        case Monster::troll: return "Troll";
        case Monster::vampire: return "Vampire";
        case Monster::zombie: return "Zombie";
        default: return "Unknown";
        }
    }

    void print() const
    {
        std::cout << m_name << " the " << getTypeName();
    
        if ( m_hit <= 0 )
            std::cout << " is dead.\n";
        else
            std::cout << " has " << m_hit << " hit points and says " << m_roar << ".\n";
    }
};

namespace MonsterGenerator
{
    std::string_view getName(int number)
    {
        switch(number)
        {
        case 0: return "Blarg";
        case 1: return "Natt";
        case 2: return "Telas";
        case 3: return "Exers";
        case 4: return "Kudos";
        case 5: return "Barlog";
        default: return "Unknown";
        }
        
    }

    std::string_view getRoar(int number)
    {
        switch(number)
        {
        case 0: return "*ROAR*";
        case 1: return "*rattle*";
        case 2: return "*shutter*";
        case 3: return "*woooes*";
        case 4: return "*junk*";
        case 5: return "*pongpong*";
        default: return "Unknown";
        }
        
    }

    Monster generate()
    {
        return Monster{ 
            static_cast<Monster::Type>( Random::get(0, Monster::maxMonsterTypes-1) ), 
            getName( Random::get(0, 5) ) , 
            getRoar( Random::get(0, 5) ), 
            Random::get(0, 100) 
            };
    }
}

int main()
{
    Monster skeleton { Monster::skeleton, "Bones", "*rattle*", 4 };
    skeleton.print();

    Monster vampire { Monster::vampire, "Nibblez", "*hiss*", 0 };
    vampire.print();

    Monster m { MonsterGenerator::generate() };
    m.print();

    return 0;
}
