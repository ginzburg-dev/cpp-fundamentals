#include "../random/random.h"
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

class Creature
{
protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};

public:
    Creature(std::string_view name, char symbol, int health, int damage, int gold)
        : m_name{name}
        , m_symbol{symbol}
        , m_health{health}
        , m_damage{damage}
        , m_gold{gold}
    {}

    void reduceHealth(int damage) { m_health -= damage; }
    bool isDead() const { return m_health <= 0; }
    void addGold(int gold) { m_gold += gold; }

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getGold() const { return m_gold; }
};

class Potion
{
public:
    enum Type
    {
        health,
        strength,
        poison,
        max_type,
    };

    enum Size
    {
        small,
        medium,
        large,
        max_size,
    };

    static constexpr int potionChance{ 30 };

    Potion(Type type, Size size)
        : m_type{type}, m_size{size}
    {}

    Type getType() const { return m_type; }
    std::string_view getName() const { return names[m_type]; }
    std::string_view getSizeName() const { return sizeNames[m_size]; }
    int getEffectValue() const { return m_potionEffectData[m_type][m_size]; }

    static Potion getRandomPotion()
    {
        return Potion{ 
            static_cast<Type>(Random::get(0, Type::max_type-1)), 
            static_cast<Size>(Random::get(0, Size::max_size-1)) 
        };
    }

private:
    Type m_type{};
    Size m_size{};

    static constexpr std::string_view names[] { "Health", "Strength", "Poison" };
    static constexpr std::string_view sizeNames[] { "Small", "Medium", "Large" };
    static constexpr int m_potionEffectData[][3] { { 2, 2, 5 }, { 1, 1, 1 }, { -1, -1, -1} };
};

class Player : public Creature
{
private:
    int m_level{1};

public:
    Player(std::string_view name)
        : Creature{name,'@', 100, 1, 0}
    {}

    int getLevel() const { return m_level; }

    void drinkPotion(Potion& potion)
    {
        switch(potion.getType())
        {
        case Potion::Type::health:
            m_health += potion.getEffectValue();
            break;
        case Potion::Type::strength:
            m_damage += potion.getEffectValue();
            break;
        case Potion::Type::poison:
            m_health += potion.getEffectValue();
            break;
        default:
            break;
        }

        std::cout << "You drank a " << potion.getSizeName() << " potion of " << potion.getName() << '\n';
    }

    void levelUp() { ++m_level; ++m_damage; }
    bool hasWon() { return m_level >= 20; }
};

class Monster : public Creature
{
    public:
    enum Type
    {
        dragon,
        orc,
        slime,
        max_types,
    };

    Monster(Type type)
        : Creature{ monsterData[type] }
    {}

    static Monster getRandomMonster()
    {
        return Monster{ static_cast<Type>(Random::get(0, max_types-1)) };
    }

private:
    static inline Creature monsterData[] {
        { "dragon", 'D', 20, 4, 100 },
        { "orc", 'o', 4, 2, 25 },
        { "slime", 's', 1, 1, 10 }
    };

    static_assert(std::size(monsterData) == max_types);
};

void onMonsteKilled(Player& player, const Monster& monster)
{
    std::cout <<  "You killed the " << monster.getName() << ".\n";
    player.levelUp();
    std::cout << "You are now level " << player.getLevel() << ".\n";
    player.addGold(monster.getGold());
    std::cout << "You found " << monster.getGold() << " gold.\n";

    if ( Random::get(1,100) <= Potion::potionChance )
    {
        std::cout << "You found a magical potion! Would you like to drink it? [y/n]: ";
        char input;
        std::cin >> input;

        if ( input == 'y' || input == 'Y' )
        {
            Potion potion{ Potion::getRandomPotion() };
            player.drinkPotion(potion);
        }
    }
}

void attackPlayer(Player& player, const Monster& monster)
{
    if (monster.isDead())
        return;

    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

void attackMonster(Player& player, Monster& monster)
{
    if (player.isDead())
        return;

    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";

    if (monster.isDead())
        onMonsteKilled(player, monster);
}

void fightMonster(Player& player)
{
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

    while ( !monster.isDead() && !player.isDead() )
    {
        std::cout << "(R)un or (F)ight: ";
        char input;
        std::cin >> input;

        if ( input == 'f' || input == 'F' )
        {
            attackMonster(player, monster);
            attackPlayer(player, monster);
        }

        if ( input == 'r' || input == 'R' )
        {
            if ( Random::get(0,1) )
            {
                std::cout << "You failed to flee.\n";
                attackPlayer(player, monster);
                continue;
            }
            else
            {
                std::cout << "You successfully fled.\n";
                return;
            }
        }
    }
}

int main()
{
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;

    Player player{name};
    std::cout << "Welcome, " << player.getName() << ".\n";

    while( !(player.hasWon() || player.isDead()) )
        fightMonster(player);

    if ( player.isDead() )
    {
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }
    else
    {
        std::cout << "You won with " << player.getGold() << " gold!\n";
    }

    return 0;
}
