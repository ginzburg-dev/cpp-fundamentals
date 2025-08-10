#include "../random/random.h"
#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <limits>

/*
Board things:
    - Display the game board
    - Display an individual tile
    - Randomize the starting state
    - Slide tiles
    - Determine if win condition reached
User things:
    - Get commands from user
    - Handle invalid input
    - Allow the user to quit before winning

Rough high-level structure of our program:
    class Tile:             Display number
    class Board:            Handle 2d array of Tile
    namespace UserInput:    Get and handle user input
    function main():        Main game logic loop

*/

namespace Settings
{
    constexpr int g_consoleLines{ 25 };
    constexpr int g_gridSize { 4 };
    constexpr int g_randomIterations { 1000 };
}

class Direction
{
public:
    enum Type
    {
        up,
        left,
        down,
        right,
        max_directions,
    };

    Direction() = default;
    Direction(Type type)
        : m_direction{ type }
    {}
    Type getDirection() const { return m_direction; }
    static Direction getRandomDirection()
    {
        return Direction{ static_cast<Type>(Random::get(0, max_directions-1)) };
    }

    Direction operator-()
    {
        switch (m_direction)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        default:    break;
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<< (std::ostream& out, const Direction& direction)
    {
        switch (direction.m_direction)
        {
        case Direction::up:     return (out << "up");
        case Direction::down:   return (out << "down");
        case Direction::left:   return (out << "left");
        case Direction::right:  return (out << "right");
        default:                break;
        }

        assert(0 && "Unsupported direction was passed!");
        return (out << "unknown direction");
    }

private:
    Type m_direction{};
};

struct Point
{
    int x{};
    int y{};

    friend bool operator==(Point p1, Point p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    friend bool operator!=(Point p1, Point p2) { return !( p1 == p2 ); }

    Point getAdjacentPoint(const Direction& direction)
    {
        switch(direction.getDirection())
        {
        case Direction::up: return { x, y - 1 };
        case Direction::down: return { x, y + 1 };
        case Direction::left: return { x - 1, y };
        case Direction::right: return { x + 1, y };
        default: return {};
        }

        assert(0 && "Unsupported direction was passed!");
        return *this;
    }
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    char getCharacter()
    {
        while (true)
        {
            char ch{};
            std::cin >> ch;
        
            if (!std::cin)
            {
                std::cin.clear();
                ignoreLine();
                continue;
            }

            ignoreLine();
            return ch;
        }
    }

    char getCommandFormUser()
    {
        char ch{};
        while(!isValidCommand(ch))
            ch = getCharacter();
        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch(ch)
        {
        case 'w': return { Direction::up };
        case 's': return { Direction::down };
        case 'a': return { Direction::left };
        case 'd': return { Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
}


class Tile
{
private:
    int m_value{ 0 };
public:
    Tile() = default;

    explicit Tile(int value)
        : m_value{value}
    {}
    
    friend std::ostream& operator<< (std::ostream& out, const Tile tile);
    friend bool operator==(const Tile& t1, const Tile& t2) { return t1.m_value == t2.m_value; }
    friend bool operator!=(const Tile& t1, const Tile& t2) { return !(t1 == t2); }
    bool isEmpty() const { return !m_value; }
    int getNum() const { return m_value; };
};

std::ostream& operator<< (std::ostream& out, const Tile tile)
{
    if (tile.m_value > 9)
        out << " " << tile.m_value << " ";
    else if (tile.m_value > 0)
        out << "  " << tile.m_value << " ";
    else if (tile.m_value == 0)
        out << "    ";

    return out;
}

class Board
{
private:
    Tile m_tiles[Settings::g_gridSize][Settings::g_gridSize]{
        Tile{ 1 }, Tile{ 2 }, Tile{ 3 }, Tile{ 4 },
        Tile{ 5 }, Tile{ 6 }, Tile{ 7 }, Tile{ 8 },
        Tile{ 9 }, Tile{ 10 }, Tile{ 11 }, Tile{ 12 },      
        Tile{ 13 }, Tile{ 14 }, Tile{ 15 }, Tile{ 0 }
    };

public:
    Board() = default;
    
    Point getEmptyPoint() const 
    {
        for ( int x = 0; x < Settings::g_gridSize; ++x)
            for ( int y = 0; y < Settings::g_gridSize; ++y) 
                if (m_tiles[y][x].isEmpty())
                    return { x, y };
        
        assert(0 && "There is no empty tile in the board!!!");
        return { -1,-1 };
    }

    static bool isValidTitlePos(Point pt)
    {
        if ( ( pt.x >= 0 && pt.x < Settings::g_gridSize )
            && ( pt.y >= 0 && pt.y < Settings::g_gridSize ) )
                return true;
        return false;
    }
    
    void swapTiles(const Point& p1, const Point& p2 )
    {
        std::swap(m_tiles[p1.y][p1.x], m_tiles[p2.y][p2.x] );
    }

    bool moveTile(Direction dir)
    {
        Point emptyPoint { getEmptyPoint() };
        Point adjacentPoint { emptyPoint.getAdjacentPoint(-dir) };

        if (!isValidTitlePos(adjacentPoint) )
            return false;
        
        swapTiles(emptyPoint, adjacentPoint);
        return true;
    }

    void randomize()
    {
        for (int i{0}; i < Settings::g_randomIterations; )
        {
            if ( moveTile(Direction::getRandomDirection()) )
                ++i;
        }
    }

    bool playerWon() const
    {
        static Board s_solved{};
        return s_solved == *this;
    }

    friend bool operator==(const Board& b1, const Board& b2);
    friend std::ostream& operator<< (std::ostream& out, const Board& board);
};

bool operator==(const Board& b1, const Board& b2)
{
    for ( int x = 0; x < Settings::g_gridSize; ++x )
        for ( int y = 0; y < Settings::g_gridSize; ++y )
            if ( b1.m_tiles[y][x] != b2.m_tiles[y][x] )
                return false;
    return true;
}

std::ostream& operator<< (std::ostream& out, const Board& board)
{
    // Print blank lines
    for (int i{0}; i < Settings::g_consoleLines; ++i)
        std::cout << '\n';
    
    for (int i { 0 }; i < Settings::g_gridSize; ++i)
    {
        for (int k { 0 }; k < Settings::g_gridSize; ++k)
            out << board.m_tiles[i][k];
        out << '\n';
    }
        
    return out;
}

int main()
{
    Board board{};
    board.randomize();

    std::cout << board;

    while(true)
    {
        char input{ UserInput::getCommandFormUser() };

        if (input == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            break;
        }

        Direction dir { UserInput::charToDirection(input) };

        if ( board.moveTile(dir) )
            std::cout << board;

        if ( board.playerWon() )
        {
            std::cout << "\n\nYou won!\n\n";
            return 0;
        }
    }

    return 0;
}
