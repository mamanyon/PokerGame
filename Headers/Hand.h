#ifndef HAND_H
#define HAND_H
#include <vector>
#include "Deck.h"
#include "Combination.h"
using namespace std;

class Hand {

public:
    Hand();
    int getScore() const;
    std::vector<Card> getCards() const;
    vector<Card> getCommunityCards() const;
    static Hand bestHand(const std::vector<Card>& holeCards, const std::vector<Card>& community_ards);
    static Hand worstHand(const std::vector<Card>& holeCards, const std::vector<Card>& community_cards);
    void addPlayerCard(Card card);
    void addCommunityCard(Card card);
    bool compareSameRankHand(const Hand& other) const;
    vector<Combination> getCombinations(string name) const;
    void clearHand();
private:
    vector<Card> player_cards;
    vector<Card> community_card;
    
    void sortByRank();
    void sortBySuit();
    
};

#endif