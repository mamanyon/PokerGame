#ifndef COMBINATION_H
#define COMBINATION_H
#include <vector>
#include <string>
#include "Deck.h"
#include "TieBreaker.h"
using namespace std;
class Combination {
    public:
        Combination(string name, vector<Card> fiveCards);
        vector<Card> fiveCards;
        string name;
        TieBreaker tieBreaker;
        TieBreaker GetBestHandRank() const;
    private:
        std::array <int, 13> CountRanks() const;
        bool IsRoyalFlush() const;
        bool IsFlush() const;
        bool IsStraight() const;
        bool IsStraightFlush() const;
        bool IsFourOfAKind() const;
        bool IsFullHouse() const;
        bool IsThreeOfAKind() const;
        bool IsTwoPair() const;
        bool IsPair() const;


};

#endif