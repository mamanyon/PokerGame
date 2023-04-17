#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
#include "../Headers/Player.h"
#include "../Headers/Game.h"
#include "../Headers/HandComparator.h"
#include "../Headers/TieBreaker.h"
#include <cassert>

  void testIsFlush() {
    std::vector<Card> cards = {
        Card(Two,Hearts),
        Card(Five,Hearts),
        Card(Seven,Hearts),
        Card(Ten,Hearts),
        Card(King,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isFlush = testCombination.IsFlush();
    assert(isFlush == true);
}

void testIsStraightFlush() {
    std::vector<Card> cards = {
        Card(Two,Hearts),
        Card(Three,Hearts),
        Card(Four,Hearts),
        Card(Five,Hearts),
        Card(Six,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isStraightFlush = testCombination.IsStraightFlush();
    assert(isStraightFlush == true);
}

void testIsFourOfAKind() {
    std::vector<Card> cards = {
        Card(Two,Hearts),
        Card(Two,Diamonds),
        Card(Two,Spades),
        Card(Two,Clubs),
        Card(Six,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isFourOfAKind = testCombination.IsFourOfAKind();
    assert(isFourOfAKind == true);
}
//more tests for the combination class functions 
void testIsFullHouse() {
    std::vector<Card> cards = {
        Card(Two,Hearts),
        Card(Two,Diamonds),
        Card(Two,Spades),
        Card(Six,Clubs),
        Card(Six,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isFullHouse = testCombination.IsFullHouse();
    assert(isFullHouse == true);
}
void testIsRoyalFlush() {
    std::vector<Card> cards = {
        Card(Ten,Hearts),
        Card(Jack,Hearts),
        Card(Queen,Hearts),
        Card(King,Hearts),
        Card(Ace,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isRoyalFlush = testCombination.IsRoyalFlush();
    assert(isRoyalFlush == true);
}

void testGetCombinations(){
    std::vector<Card> player_cards = {
        Card(Two,Hearts),
        Card(Two,Diamonds),
        Card(Two,Spades),
        Card(Six,Clubs)
    };
    vector<Card> community_cards = {
        Card(Ten,Hearts),
        Card(Six,Spades),
        Card(Queen,Hearts),
        Card(Seven,Hearts),
        Card(Ace,Hearts)
    };
    Hand hand(player_cards, community_cards);
    vector<Combination> combinations = hand.getCombinations("sa");
    //print combinations
    for (int i = 0; i < combinations.size(); i++){
        combinations[i].PrintHand();
        cout << ""<<endl;
    }
    cout << "Number of combinations: " << combinations.size() << endl;
}
//test compareHands function in HandComparator class
void testCompareHands(){
    std::vector<Card> player_cards = {
        Card(Two,Hearts),
        Card(Two,Diamonds),
        Card(Three,Spades),
        Card(Six,Clubs)
    };
    vector<Card> community_cards = {
        Card(Ten,Hearts),
        Card(Six,Spades),
        Card(Queen,Hearts),
        Card(Seven,Hearts),
        Card(Ace,Hearts)
    };
    Hand hand(player_cards, community_cards);
    HandComparator handComparator;
    vector<Combination> combinations = hand.getCombinations("sa");
    //print combinations
    for (int i = 0; i < combinations.size()-1; i++){
        int num = handComparator.compareHands(combinations[i], combinations[i+1]);
        cout << "the number is : " << num <<endl;
        //check tiebreaker compare function
        TieBreaker tieBreaker1 = combinations[i].tieBreaker;
        TieBreaker tieBreaker2 = combinations[i+1].tieBreaker;
        int num2 = tieBreaker1.Compare(tieBreaker2);
        cout << "the number of compare tie breaker is : " << num2 <<endl;
    }
    


    cout << "Number of combinations: " << combinations.size() << endl;
    sort(combinations.begin(), combinations.end(), HandComparator::compareHands);
}
int main() {
    testIsFlush();
    testIsStraightFlush();
    testIsFourOfAKind();
    testIsFullHouse();
    testIsRoyalFlush();
    std::cout << "All tests passed!" << std::endl;
    testCompareHands();
    return 0;
}


