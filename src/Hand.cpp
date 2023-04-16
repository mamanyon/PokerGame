#include "../Headers/Hand.h"
#include <algorithm>
#include <iostream>
using namespace std;
Hand::Hand() : player_cards(), community_card() {
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


vector<Combination> Hand::getCombinations(string name) const {
    //returns a vector of all fiveCards combinations that name can possibly get from his cards-
    //where 3 cards are from the community cards and 2 cards are from the player cards
    vector<Combination> combinations;
    //5 choose 3 multiply by 4 choose 2 == 60 .
    int numPlayerCards = player_cards.size();
    int numCommunityCards = community_card.size();

    // Generate all possible combinations of 2 player cards
    for (int i = 0; i < numPlayerCards - 1; i++) {
        for (int j = i + 1; j < numPlayerCards; j++) {
            vector<Card> handCards = {player_cards[i], player_cards[j]};

            // Generate all possible combinations of 3 community cards
            for (int k = 0; k < numCommunityCards - 2; k++) {
                for (int l = k + 1; l < numCommunityCards - 1; l++) {
                    for (int m = l + 1; m < numCommunityCards; m++) {
                        vector<Card> fiveCards = handCards;
                        fiveCards.push_back(community_card[k]);
                        fiveCards.push_back(community_card[l]);
                        fiveCards.push_back(community_card[m]);
                        Combination combination(name, fiveCards);
                        combinations.push_back(combination);
                    }
                }
            }
        }
    }
    return combinations; 
}
void Hand::clearHand() {
    player_cards.clear();
    community_card.clear();
}








