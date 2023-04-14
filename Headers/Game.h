#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"
#include "HandComparator.h"
#include <algorithm>
using namespace std;
class Game{
public:
    Game();
    void run();
    vector <Card> communityCards;
    int getNumPlayers() const;
private:    
    int num_players;
    int currentPlayerIndex;
    int pot;//the total amount of money in the pot
    const int bigBlind = 10;
    const int smallBlind = 5;
    Deck deck;
    vector <Player> players;
    bool isGameOver;
    bool isRoundOver;
    void bettingRound(int minimumBet);
    void printCommunityCards() const;
    void checkForWinner();
    void dealHoleCards();
    void bettingPreFlop();
    void dealFlop();
    void bettingPostFlopOrTurnOrRiver();
    void dealTurnOrRiver();
    void DetermineWinner();
    void StartingRound();
    void ResetRound();
    bool EndGame();

};
#endif
