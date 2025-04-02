#include <algorithm>
#include <iostream>
#include <array>
#include <string_view>
#include <cassert>
#include "../random/random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,
    
        max_ranks
    };
    
    enum Suit
    {
        suit_clubs,
        suit_diamond,
        suit_heart,
        suit_spade,
    
        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7,
        rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };

    static constexpr std::array allSuits { suit_clubs, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card& card)
    {
        static constexpr std::array rankNames {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'}; 
        static constexpr std::array suitNames {'C', 'D', 'H', 'S'};

        out << rankNames[card.rank] << suitNames[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Desk
{
private:
    std::array<Card, 52> m_cards{};
    std::size_t m_nextCard {0};

public:
    Desk()
    {
        std::size_t index{0};
        for (auto suit : Card::allSuits )
            for (auto rank : Card::allRanks )
                m_cards[index++] = Card { rank, suit };
    }

    Card dealCard()
    {
        assert( m_nextCard != 52 && "Deck::dealCard ran out of cards" );
        return m_cards[m_nextCard++];
    }

    void shuffle()
    {
        m_nextCard = 0;
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
    }
};

int main()
{

    Card card{ Card::rank_2, Card::suit_heart };
    std::cout << card << '\n';

    for (auto suit : Card::allSuits )
        for (auto rank : Card::allRanks )
            std::cout << Card{ rank, suit } << ' ';
    std::cout << '\n';

    Desk desk{};

    std::cout << desk.dealCard() << ' ' << desk.dealCard() << ' ' << desk.dealCard() << '\n';

    desk.shuffle();
    std::cout << desk.dealCard() << ' ' << desk.dealCard() << ' ' << desk.dealCard() << '\n';

    return 0;
}
