#include "../Headers/Hand.h"
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
Hand::Hand() : player_cards(), community_card() {
    // std::sort(this->cards.begin(), this->cards.end(), [](const Card& c1, const Card& c2) {
    //     return c1.rank > c2.rank;
    // });
}
Hand::Hand(const std::vector<Card>& holeCards, const std::vector<Card>& community_cards) : player_cards(holeCards), community_card(community_cards) {
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


bool checkDuplicate(vector<Card> &fiveCards, vector<Card> &existingFiveCards) {
    for (int i = 0; i < 5; i++) {
        if (fiveCards[i].rank != existingFiveCards[i].rank || fiveCards[i].suit != existingFiveCards[i].suit) {
            return false;
        }
    }
    return true;
}
vector<Combination> Hand::getCombinations(string name) const {
    vector<Combination> combinations;
    const int num_player_cards = player_cards.size();
    const int num_community_cards = community_card.size();
    vector<Card> cards(5);

    for (int i = 0; i < num_player_cards; i++) {
        for (int j = i + 1; j < num_player_cards; j++) {
            for (int k = 0; k < num_community_cards; k++) {
                for (int l = k + 1; l < num_community_cards; l++) {
                    for (int m = l + 1; m < num_community_cards; m++) {
                        // Construct the 5-card combination
                        vector<Card> fiveCards;
                        fiveCards.push_back(player_cards[i]);
                        fiveCards.push_back(player_cards[j]);
                        fiveCards.push_back(community_card[k]);
                        fiveCards.push_back(community_card[l]);
                        fiveCards.push_back(community_card[m]);
                        
                        // Sort the cards so that we can detect duplicates
                        sort(fiveCards.begin(), fiveCards.end(), [](const Card& a, const Card& b) {
                            return a.rank < b.rank || (a.rank == b.rank && a.suit < b.suit);
                        });
                        
                        // Check if the combination is already in the result vector
                        bool isDuplicate = false;
                        for (Combination& existingCombination : combinations) {
                            if(checkDuplicate(fiveCards, existingCombination.fiveCards)) {
                                isDuplicate = true;
                                break;
                            }
                        }
                    
                        // If it's not a duplicate, add it to the result vector
                        if (!isDuplicate) {
                            combinations.push_back(Combination(name, fiveCards));                            
                        }
                        
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








