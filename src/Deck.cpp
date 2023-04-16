#include "../Headers/Deck.h"
#include <iostream>
#include <algorithm> // for shuffle
#include <stdexcept>
#include <chrono>
#include <random>
#include <cassert>
using namespace std;


Deck::Deck() {
    // Create a deck of 52 cards
    for (int suit = Spades; suit <= Clubs; suit++) {
        for (int rank = Two; rank <= Ace; rank++) {
            cards.push_back(Card{static_cast<Rank>(rank), static_cast<Suit>(suit)});
        }
    }
    shuffle();
}

void Deck::shuffle() {
    //used for random shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card Deck::dealCard() {
    // Check if there are any cards left in the deck
    if (cards.size() <= 0) {
        throw runtime_error("No cards left in the deck!");
    }

    // Deal the next card and update the current card index
    Card card = cards[cards.size() - 1];
    cards.pop_back();
    return card;
}
