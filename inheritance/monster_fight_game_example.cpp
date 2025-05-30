#include "../random/random.h"
#include <iostream>
#include <array>
#include <cstddef>
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
    enum class Type { health, strength, poison, max_types };
    enum class Size { small, medium, large, max_sizes };

    static constexpr int potionChance{ 30 };

    Potion(Type type, Size size)
        : m_type{type}, m_size{size}
    {}

    Type getType() const { return m_type; }
    Size getSize() const { return m_size; }

    std::string_view getTypeName() const { return typeNames[static_cast<std::size_t>(m_type)]; }
    std::string_view getSizeName() const { return sizeNames[static_cast<std::size_t>(m_size)]; }
    int getEffectValue() const { return effectTable[static_cast<std::size_t>(m_type)][static_cast<std::size_t>(m_size)]; }

    static Potion getRandomPotion()
    {
        return Potion{ 
            static_cast<Type>(Random::get(0, static_cast<int>(Type::max_types)-1)), 
            static_cast<Size>(Random::get(0, static_cast<int>(Size::max_sizes)-1)) 
        };
    }

private:
    Type m_type{};
    Size m_size{};

    static constexpr std::array<std::string_view, static_cast<std::size_t>(Type::max_types)> typeNames { "Health", "Strength", "Poison" };
    static constexpr std::array<std::string_view, static_cast<std::size_t>(Size::max_sizes)> sizeNames { "Small", "Medium", "Large" };
    static constexpr std::array<std::array<int, static_cast<std::size_t>(Size::max_sizes)>, static_cast<std::size_t>(Type::max_types)> effectTable 
        {{ 
            { 2, 2, 5 },
            { 1, 1, 1 },
            { -1, -1, -1}
        }};

    static_assert( typeNames.size() == static_cast<std::size_t>(Type::max_types) );
    static_assert( sizeNames.size() == static_cast<std::size_t>(Size::max_sizes) );

    static_assert( effectTable.size() == static_cast<std::size_t>(Type::max_types) );
    static_assert( effectTable[0].size() == static_cast<std::size_t>(Size::max_sizes) );
};

class Player : public Creature
{
private:
    int m_level{1};

public:
    Player(std::string_view name)
        : Creature{name,'@', 10, 1, 0}
    {}

    int getLevel() const { return m_level; }
    bool hasWon() const { return m_level >= 20; }

    void levelUp() 
    { 
        ++m_level;
        ++m_damage;
    }

    void drinkPotion(const Potion& potion)
    {
        switch(potion.getType())
        {
        case Potion::Type::health:
        case Potion::Type::poison:
            m_health += potion.getEffectValue();
            break;
        case Potion::Type::strength:
            m_damage += potion.getEffectValue();
            break;
        default:
            break;
        }

        if ( m_health < 0 )
            m_health = 0;

        std::cout << "You drank a " << potion.getSizeName() << " potion of " << potion.getTypeName() << '\n';
    }
};

class Monster : public Creature
{
public:
    enum class Type { dragon, orc, slime, max_types };

    Monster(Type type)
        : Creature{ monsterData[static_cast<std::size_t>(type)] }
    {}

    static Monster getRandomMonster()
    {
        auto type = static_cast<Type>(Random::get(0, static_cast<int>(Type::max_types)-1));
        return Monster{ type };
    }

private:
    static inline const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData {{
        { "dragon", 'D', 20, 4, 100 },
        { "orc", 'o', 4, 2, 25 },
        { "slime", 's', 1, 1, 10 }
    }};

    static_assert(monsterData.size() == static_cast<std::size_t>(Type::max_types));
};

void onMonsterKilled(Player& player, const Monster& monster)
{
    std::cout <<  "You killed the " << monster.getName() << ".\n";
    player.levelUp();
    std::cout << "You are now level " << player.getLevel() << ".\n";
    player.addGold(monster.getGold());
    std::cout << "You found " << monster.getGold() << " gold.\n";

    if ( Random::get(1,100) <= Potion::potionChance )
    {
        char input{};
        while ( input != 'y' && input != 'n' )
        {
            std::cout << "You found a magical potion! Would you like to drink it? [y/n]: ";
            std::cin >> input;
            input = std::tolower(input);
        }
        
        if ( input == 'y' )
        {
            Potion potion{ Potion::getRandomPotion() };
            player.drinkPotion(potion);
        }
    }
}

void attackPlayer(Player& player, const Monster& monster)
{
    if (monster.isDead()) return;
    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

void attackMonster(Player& player, Monster& monster)
{
    if (player.isDead()) return;
    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
    if (monster.isDead())
        onMonsterKilled(player, monster);
}

void fightMonster(Player& player)
{
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";

    while ( !monster.isDead() && !player.isDead() )
    {
        char input{};
        while ( input != 'f' && input != 'r' )
        {
            std::cout << "(R)un or (F)ight: ";
            std::cin >> input;
            input = std::tolower(input);
        }
        
        if ( input == 'f' )
        {
            attackMonster(player, monster);
            attackPlayer(player, monster);
        }
        else if ( input == 'r' )
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
