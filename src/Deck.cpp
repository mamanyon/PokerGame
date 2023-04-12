#include "deck.h"
#include <algorithm> // for shuffle
#include <stdexcept>
#include <chrono>
#include <random>
using namespace std;


Deck::Deck() {
    // Create a deck of 52 cards
    for (int suit = Clubs; suit <= Spades; suit++) {
        for (int rank = Two; rank <= Ace; rank++) {
            cards.push_back(Card{static_cast<Rank>(rank), static_cast<Suit>(suit)});
        }
    }
    topCardIndex = 0;
    shuffle();
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    topCardIndex = 0;
}

Card Deck::dealCard() {
    
    // Check if there are any cards left in the deck
    if (topCardIndex >= cards.size()) {
        throw runtime_error("No cards left in the deck!");
    }

    // Deal the next card and update the current card index
    Card card = cards[topCardIndex];
    topCardIndex++;
    return card;
}
