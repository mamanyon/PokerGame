#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
#include "Player.h"
#include "Game.h"

// // Define a deck of cards
// vector<Card> deck;

// // Define a player struct to represent a single player
// struct Player {
//     string name;
//     vector<Card> hand;
//     int chips;
//     bool is_active;
// };

// // Define the community cards
// vector<Card> community_cards;

// // Define the pot
// int pot;

// // Define a function to initialize the deck of cards
// void init_deck() {
//     for (int i = Two; i <= Ace; i++) {
//         for (int j = Clubs; j <= Spades; j++) {
//             deck.push_back(Card{ static_cast<Rank>(i), static_cast<Suit>(j) });
//         }
//     }
// }

// // Define a function to shuffle the deck of cards
// void shuffle_deck() {
//     random_device rd;
//     mt19937 g(rd());
//     shuffle(deck.begin(), deck.end(), g);
// }

// // Define a function to deal the cards to the players
// void deal_cards(vector<Player>& players) {
//     for (int i = 0; i < 4; i++) {
//         for (auto& player : players) {
//             player.hand.push_back(deck.back());
//             deck.pop_back();
//         }
//     }
// }

// // Define a function to deal the flop
// void deal_flop() {
//     for (int i = 0; i < 3; i++) {
//         community_cards.push_back(deck.back());
//         deck.pop_back();
//     }
// }

// // Define a function to deal the turn
// void deal_turn() {
//     community_cards.push_back(deck.back());
//     deck.pop_back();
// }

// // Define a function to deal the river
// void deal_river() {
//     community_cards.push_back(deck.back());
// deck.pop_back();
// }
// // Define a function to determine the winner of the game
// vector<Player> determine_winner(vector<Player>& players) {
// // TODO: implement logic to determine the winner
// return players;
// }


int main()
{
	char con;
    Game game;
    int num_of_players= game.getNumPlayers();
    int index=0;
	do{
	
	game.run(index);

	cout<<"Do you want to play again (y for yes, n for no): "<<endl;
	cin>>con;
    index++;
    index = index % num_of_players;

	}while(con=='y' || con=='Y');

    return 0;
}
