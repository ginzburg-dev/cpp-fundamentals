#include "../random/random.h"
#include <iostream>
#include <vector>
#include <string>
#include <string_view>

using namespace std::literals::string_view_literals;

namespace Settings
{
    constexpr int wrongGuessesAllowed { 6 };
}

namespace WordList
{
    std::vector words { "mystery"sv, "broccoli"sv , "account"sv, "almost"sv, "spaghetti"sv, "opinion"sv, "beautiful"sv, "distance"sv, "luggage"sv };

    std::string_view getRandomWord()
    {
        return words[ Random::get<std::size_t>(0, words.size()-1) ];
    }
}

class Session
{
private:
    std::string_view m_word { WordList::getRandomWord()};
    std::vector<char> m_wrongGuessedLetters{};
    std::vector<char> m_guessedLetters{};

public:
    std::string_view getWord() const { return m_word; };
    int wrongGuessLeft() const { return Settings::wrongGuessesAllowed - std::ssize(m_wrongGuessedLetters); };
    const std::vector<char>& getGuessedLetters() const { return m_guessedLetters; };
    void setGuess(char c) { m_guessedLetters.push_back(c); };
    const std::vector<char>& getWrongGuessedLetters() const { return m_wrongGuessedLetters; };
    void setWrongGuess(char c) { m_wrongGuessedLetters.push_back(c); };
    bool isLetterInWord(char c) const;
    bool isLetterGuessed(char c) const;
    bool won() const;
};

bool Session::isLetterInWord(char c) const
{
    for (auto i : m_word)
    {
        if( c == i )
            return true;
    }
    return false;
};

bool Session::isLetterGuessed(char c) const
{
    for (auto i : m_guessedLetters)
    {
        if( c == i )
            return true;
    }

    return false;
};

bool Session::won() const
{
    for (auto i : m_word)
    {
        if ( !isLetterGuessed(i) )
            return false;
    }

    return true;
};

void draw(const Session& s)
{
    std::cout << "The word: ";
    
    for( auto i : s.getWord() )
    {
        if ( s.isLetterGuessed(i) )
            std::cout << i;
        else
            std::cout << '_';
    }

    std::cout  << " Wrong guesses: ";

    for (std::size_t i {0}; i < s.wrongGuessLeft(); ++i)
        std::cout << '+';
    
    for (auto i : s.getWrongGuessedLetters() )
        std::cout << i;
    std::cout << '\n';
}

char getGuess(const Session& s)
{
    while (true)
    {
        std::cout << "Enter your next letter: ";
        char c{};
        std::cin >> c;

        if ( !std::cin )
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That wasn't a valid input. Try again.\n\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if ( (c < 'a') || ( c > 'z' ) )
        {
            std::cout << "That wasn't a valid input. Try again.\n\n";
            continue;
        }

        if ( s.isLetterGuessed(c) )
        {
            std::cout << "You already guessed that. Try again.\n\n";
            continue;
        }

        return c;
    }
}

void handleGuess(Session& s, char c)
{
    if ( s.isLetterInWord(c) )
    {
        std::cout << "Yes, '" << c << "' is in the word!\n\n";
        s.setGuess(c);
    } else
    {
        std::cout << "No, '" << c << "' is not in the word!\n\n";
        s.setWrongGuess(c);
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n" <<
        "To win: guess the word.  To lose: run out of pluses.\n";

    Session s;

    while( !s.won() && s.wrongGuessLeft() )
    {
        draw(s);
        char c { getGuess(s) };
        handleGuess(s, c);
    }

    draw(s);

    if( !s.wrongGuessLeft() )
        std::cout << "You lost! The word was: " << s.getWord() << '\n';
    else
        std::cout << "You won!\n";

    return 0;
}
