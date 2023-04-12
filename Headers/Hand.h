#ifndef HAND_H
#define HAND_H
#include <vector>
#include "Deck.h"
using namespace std;
class Hand {

public:
    Hand();
    int getScore() const;
    std::vector<Card> getCards() const;
    static Hand bestHand(const std::vector<Card>& holeCards, const std::vector<Card>& community_ards);
    static Hand worstHand(const std::vector<Card>& holeCards, const std::vector<Card>& community_cards);
    void addPlayerCard(Card card);
    void addCommunityCard(Card card);
    
private:
    vector<Card> player_cards;
    vector<Card> community_card;

    void sortByRank();
    void sortBySuit();
    bool isFlush() const;
    bool isStraight() const;
    bool isStraightFlush() const;
    bool isFourOfAKind() const;
    bool isFullHouse() const;
    bool isThreeOfAKind() const;
    bool isTwoPair() const;
    bool isPair() const;
};

#endif