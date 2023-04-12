#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"
using namespace std;
class Game{
public:
    Game();
    void run(int index);
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
    

    void checkForWinner();
    void dealHoleCards();
    void bettingPreFlop();
    void dealFlop();
    void bettingPostFlop();
    void bettingPostTurn(); // --\/\/\/
    void bettingPostRiver(); // might be the same func isn't it ? 
    void dealTurnOrRiver();
    void determineWinner();

};
#endif
