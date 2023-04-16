
#include "../Headers/Combination.h"
#include "../Headers/Deck.h"
#include <iostream>
#include <cassert>

class Tests{
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


int main() {
    testIsFlush();
    testIsStraightFlush();
    testIsFourOfAKind();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
};

