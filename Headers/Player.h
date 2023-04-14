#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Deck.h"
#include "Hand.h"

using namespace std;
class Player {
private:
    string name;
    Hand hand;//4 cards + 3 cards from community cards.
    int chips;
    bool isactive;
    int currentBet;
    

public:
    vector<Combination> getCombinations() const;
    void ResetCurrentBet();
    int getCurrentBet() const;
    void printHoleCards() const;
    Player(string name, int chips);
    void receiveHoleCard(Card card);
    void receiveCommunityCard(Card card);
    void clearHand();
    Hand getHand() const;
    int getChips() const;
    void addChips(int amount);
    void subtractChips(int amount);
    string getName() const;
    bool isActive() const;
    void fold();
    void bet(int amount);
    vector<Card> getBestHand();
    void calculateActiveHand(const vector<Card>& communityCards);
    void Deactivate();
    void Activate();

};

#endif
