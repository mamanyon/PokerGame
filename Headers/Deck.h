#ifndef DECK_H
#define DECK_H

#include <vector>
using namespace std;
enum Rank {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace=14
};
enum Suit {
    Spades,
    Hearts,
    Diamonds,
    Clubs
};

// Define a card struct to represent a single playing card
struct Card {
    Rank rank;
    Suit suit;
    int getValue() const{
        return rank;}
    void setValue(int value){
        rank = (Rank)value;
    }
    int getSuit() const{
        return suit;
    }
    std::string toString() const {
    const std::string rankStrings = "23456789TJQKA";
    const std::string suitStrings = "CDHS";
    const std::string cardString = rankStrings.substr(rank - 2, 1) + suitStrings.substr(suit * 1, 1);
    return cardString;
}

};

class Deck {
private:
    vector<Card> cards;
    int topCardIndex;

public:
    Deck();
    void shuffle();
    Card dealCard();
};

#endif