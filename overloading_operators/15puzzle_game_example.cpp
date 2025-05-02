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
}

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


}

class Board;

class Tile
{
private:
    int m_value{ 0 };
public:
    Tile() = default;

    explicit Tile(int value)
        : m_value{value}
    {}
    
    friend Board;
    friend std::ostream& operator<< (std::ostream& out, const Tile tile);
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
    std::array<std::array<Tile, Settings::g_gridSize>, Settings::g_gridSize> m_tiles{};

public:
    Board()
    {
        for (int i { 0 }; i < Settings::g_gridSize*Settings::g_gridSize - 1; ++i)
            m_tiles[i / Settings::g_gridSize][i % Settings::g_gridSize].m_value = i + 1;

    }

    friend std::ostream& operator<< (std::ostream& out, const Board& board);
};

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
    std::cout << board;

    while(true)
    {
        char input{ UserInput::getCommandFormUser() };
        
        std::cout << "Valid command: " << input << '\n';

        if (input == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            break;
        }
    }
    
    return 0;
}
