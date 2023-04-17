#include "../Headers/Hand.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
TieBreaker::TieBreaker():rank(HandRank::HIGH_CARD), strongestCards(vector<Card>()){}
TieBreaker::TieBreaker(HandRank rank, vector<Card> fiveCards) {
    this->rank=rank;
    strongestCards=determineStrongestCards(fiveCards);
}

vector<Card> TieBreaker::determineStrongestCards(vector<Card> &fiveCards) {
    vector<Card> strongestCards;
    switch(rank){
        case PAIR:
            HandlePair(fiveCards, strongestCards);
            break;
        case TWO_PAIR:
            HandleTwoPair(fiveCards, strongestCards);
            break;
        case THREE_OF_A_KIND:
            HandleThreeOfAKind(fiveCards, strongestCards);
            break;
        case STRAIGHT:
            HandleStraight(fiveCards, strongestCards);
            break;
        case FLUSH:
            HandleFlush(fiveCards, strongestCards);
            break;
        case FULL_HOUSE:
            HandleFullHouse(fiveCards, strongestCards);
            break;
        case FOUR_OF_A_KIND:
            HandleFourOfAKind(fiveCards, strongestCards);
            break;
        case STRAIGHT_FLUSH:
            HandleStraightFlush(fiveCards, strongestCards);
            break;
        case ROYAL_FLUSH:
            HandleHighCard(fiveCards, strongestCards);
            break;
        default : //HIGH_CARD
            HandleHighCard(fiveCards, strongestCards);
            break;   
    }
    return strongestCards;
}

void TieBreaker::HandlePair(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //push the pair to the strongest cards and delete the pair from the five cards
    for(int i=0; i<fiveCards.size(); i++){
        for(int j=i+1; j<fiveCards.size(); j++){
            if(fiveCards[i].getValue()==fiveCards[j].getValue()){
                strongestCards.push_back(fiveCards[i]);
                fiveCards.erase(fiveCards.begin()+j);
                fiveCards.erase(fiveCards.begin()+i);
                break;
            }
        }
    }
    //push the rest of the cards sorted in descending order
    sort(fiveCards.begin(), fiveCards.end(), [](const Card& c1, const Card& c2) {
        return c1.getValue() > c2.getValue();
    });
    for(int i=0; i<fiveCards.size(); i++){
        strongestCards.push_back(fiveCards[i]);
    }
}
void TieBreaker::HandleHighCard(vector<Card> &fiveCards, vector<Card> &strongestCards) {
        //push the five cards sorted in descending order
        sort(fiveCards.begin(), fiveCards.end(), [](const Card& c1, const Card& c2) {
            return c1.getValue() > c2.getValue();
        });
        for(int i=0; i<fiveCards.size(); i++){
            strongestCards.push_back(fiveCards[i]);
        }
}
void TieBreaker::HandleTwoPair(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //push the two pairs to the strongest cards and delete the pairs from the five cards
    for(int i=fiveCards.size()-1; i>=0; i--){
        for(int j=i-1; j>=0; j--){
            if(fiveCards[i].getValue()==fiveCards[j].getValue()){
                strongestCards.push_back(fiveCards[i]);
                fiveCards.erase(fiveCards.begin()+i);
                fiveCards.erase(fiveCards.begin()+j);
            }
        }
    }//iterates over the vector in reverse order, starting from the end and going backwards to the beginning.
    //This ensures that erasing elements from the vector doesn't affect the position of the remaining elements that still need to be checked.
    
    
    //sort strongest cards in descending order
    sort(strongestCards.begin(), strongestCards.end(), [](const Card& c1, const Card& c2) {
        return c1.getValue() > c2.getValue();
    });
    //push the last card to the strongest cards
    strongestCards.push_back(fiveCards[0]);
}
void TieBreaker::HandleThreeOfAKind(vector<Card> &fiveCards, vector<Card> &strongestCards) {
//push the three of a kind to the strongest cards and delete the three of a kind from the five cards
    for(int i=0; i<fiveCards.size(); i++){
        for(int j=i+1; j<fiveCards.size(); j++){
            for(int k=j+1; k<fiveCards.size(); k++){
                if(fiveCards[i].getValue()==fiveCards[j].getValue() && fiveCards[i].getValue()==fiveCards[k].getValue()){
                    strongestCards.push_back(fiveCards[i]);
                    fiveCards.erase(fiveCards.begin()+k);
                    fiveCards.erase(fiveCards.begin()+j);
                    fiveCards.erase(fiveCards.begin()+i);
                    break;
                }
            }
        }
    }
}   
void TieBreaker::HandleStraight(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //so we sort first the five cards in ascending order
    sort(fiveCards.begin(), fiveCards.end(), [](const Card& c1, const Card& c2) {
        return c1.getValue() < c2.getValue();
    });
    //we check if the first card is 2 and the last card is 14
    if(fiveCards[0].getValue()==2 && fiveCards[4].getValue()==14){ //just for the case of a straight (2,3,4,5,14)
        //if it is, we change the value of the 14 to 1
        fiveCards[4].setValue(1);  
    }
    //then we sort the five cards in descending order
    //and we push the five cards to the strongest cards
    HandleHighCard(fiveCards, strongestCards);
}
void TieBreaker::HandleFlush(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //we sort the five cards in descending order
    //and we push the five cards to the strongest cards
    HandleHighCard(fiveCards, strongestCards);
}
void TieBreaker::HandleFullHouse(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //push the three of a kind to the strongest cards and delete the three of a kind from the five cards
    HandleThreeOfAKind(fiveCards, strongestCards);
    //push one of the pair to strongestcards. we know that the pair is the last two cards
    strongestCards.push_back(fiveCards[0]);
}       
void TieBreaker::HandleFourOfAKind(vector<Card> &fiveCards, vector<Card> &strongestCards) {
    //push the four of a kind to the strongest cards and delete the four of a kind from the five cards
    for(int i=0; i<fiveCards.size(); i++){
        for(int j=i+1; j<fiveCards.size(); j++){
            for(int k=j+1; k<fiveCards.size(); k++){
                for(int l=k+1; l<fiveCards.size(); l++){
                    if(fiveCards[i].getValue()==fiveCards[j].getValue() && fiveCards[i].getValue()==fiveCards[k].getValue() && fiveCards[i].getValue()==fiveCards[l].getValue()){
                        strongestCards.push_back(fiveCards[i]);
                        fiveCards.erase(fiveCards.begin()+l);
                        fiveCards.erase(fiveCards.begin()+k);
                        fiveCards.erase(fiveCards.begin()+j);
                        fiveCards.erase(fiveCards.begin()+i);
                        break;
                    }
                }
            }
        }
    }
    //push the last card to the strongest cards
    strongestCards.push_back(fiveCards[0]);
}
void TieBreaker::HandleStraightFlush(vector<Card> &fiveCards, vector<Card> &strongestCards) {
//just like handle straight
    HandleStraight(fiveCards, strongestCards);
}


bool TieBreaker::Compare(TieBreaker &other) {


    //compare the strongest cards of each hand
    for(int i=0; i<strongestCards.size(); i++){
        if(strongestCards[i].getValue()>other.strongestCards[i].getValue()){
            return true;
        }
        else if(strongestCards[i].getValue()<other.strongestCards[i].getValue()){
            return false;
        }
    }
    return false;
}