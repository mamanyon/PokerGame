#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
#include "../Headers/Player.h"
#include "../Headers/Game.h"
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


int main() {
    testIsFlush();
    testIsStraightFlush();
    testIsFourOfAKind();
    testIsFullHouse();
    testIsRoyalFlush();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}


