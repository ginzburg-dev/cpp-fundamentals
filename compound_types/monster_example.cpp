#include <iostream>
#include <string>
#include <string_view>

struct Monster
{
    enum Type
    {
        ogre,
        dragon,
        orc,
        spider,
        slime,
    };
    std::string name {};
    Type type {};
    int health { 100 };
};

constexpr std::string_view getMonsterName(Monster::Type type)
{
    switch (type)
    {
    case Monster::dragon: return "Dragon";
    case Monster::ogre: return "Ogre";
    case Monster::orc: return "Orc";
    case Monster::slime: return "Slime";
    case Monster::spider: return "Spider";
    }

    return "Unknown";
}

void printMonster(const Monster& monster)
{
    std::cout << "This " << getMonsterName(monster.type) << " is named " << monster.name << " and has " << monster.health << " health.\n";
}

int main()
{
    Monster monster1 { "Torg", Monster::ogre, 145 };
    Monster monster2 { "Blurp", Monster::slime, 23 };

    printMonster(monster1);
    printMonster(monster2);

    return 0;
}
