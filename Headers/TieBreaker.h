#ifndef TIEBREAKER_H
#define TIEBREAKER_H
#include <vector>
#include "../Headers/Deck.h"
#include "../Headers/Combination.h"
using namespace std;
enum HandRank {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};
class TieBreaker {
    public:
        TieBreaker();
        TieBreaker(HandRank rank, vector<Card> fiveCards);
        HandRank rank;
        vector<Card> strongestCards;
        int Compare(TieBreaker &other);
    private:
        vector<Card> determineStrongestCards(vector<Card> &fiveCards);
        void HandlePair(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleTwoPair(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleThreeOfAKind(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleStraight(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleFlush(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleFullHouse(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleFourOfAKind(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleStraightFlush(vector<Card> &fiveCards, vector<Card> &strongestCards);
        void HandleHighCard(vector<Card> &fiveCards, vector<Card> &strongestCards);
        
        
        
        };
#endif