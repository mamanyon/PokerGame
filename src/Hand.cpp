#include "Hand.h"
#include "Comparator.h"
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

bool Hand::operator<(const Hand& other) const {
    return Comparator::compareHands(*this, other) < 0;
}

bool Hand::operator==(const Hand& other) const {
    return Comparator::compareHands(*this, other) == 0;
}
