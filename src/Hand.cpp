#include "Hand.h"
#include <algorithm>
#include <iostream>
using namespace std;
Hand::Hand() : player_cards(vector<Card>()), community_card(vector<Card>()) {
    // std::sort(this->cards.begin(), this->cards.end(), [](const Card& c1, const Card& c2) {
    //     return c1.rank > c2.rank;
    // });
}


void Hand::addPlayerCard(Card card) {
    player_cards.push_back(card);
}
void Hand::addCommunityCard(Card card) {
    community_card.push_back(card);
}


vector<Card> Hand::getCards() const {
    return player_cards;
}
vector<Card> Hand::getCommunityCards() const {
    return community_card;
}

bool Hand::isFlush() const {
    std::unordered_map<int, int> suitCount;
    for (const auto& card : community_card) {
        suitCount[card.getSuit()]++;
    }//counted the number of cards of each suit in the community cards
    std::vector<Card> usedCards = player_cards;
    std::sort(usedCards.begin(), usedCards.end());//sort in ascending order 
    int usedCardsCount = 0;
    for (const auto& card : community_card) {
        if (card.getSuit() == usedCards[0].getSuit() && usedCardsCount < 2) {
            usedCardsCount++;
            usedCards.push_back(card);
        }
    }
    if (usedCardsCount == 2) {
        suitCount[usedCards[0].getSuit()] += 2;
        suitCount[usedCards[2].getSuit()] += 1;
        for (const auto& count : suitCount) {
            if (count.second >= 5) {
                return true;
            }
        }
    }
    return false;
}
vector<Combination> Hand::getCombinations(string name) const {
    //returns a vector of all fiveCards combinations that name can possibly get from his cards-
    //where 3 cards are from the community cards and 2 cards are from the player cards
    vector<Combination> combinations;
    //5 choose 3 multiply by 4 choose 2 .

    return combinations;
    
}
void Hand::clearHand() {
    player_cards.clear();
    community_card.clear();
}








