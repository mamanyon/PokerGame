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
void testIsStraight() {
    std::vector<Card> cards = {
        Card(Two,Hearts),
        Card(Three,Hearts),
        Card(Four,Hearts),
        Card(Five,Hearts),
        Card(Six,Hearts)
    };
    Combination testCombination("Test combination", cards);
    bool isStraight = testCombination.IsStraight();
    assert(isStraight == true);
    isStraight = testCombination.IsStraightFlush();
    assert(isStraight == true);
    isStraight = testCombination.IsThreeOfAKind();
    assert(isStraight == false);
}
void testCountRanks(){
     // Create a combination of five cards with different ranks
    Combination combination("JONATHAN",{{Card(Rank::Two, Suit::Hearts), Card(Rank::Four, Suit::Spades),
                               Card(Rank::Six, Suit::Clubs), Card(Rank::Eight, Suit::Diamonds),
                               Card(Rank::Ten, Suit::Hearts)}});
    // create a combination with two cards with rank 2 and three cards with rank 3
    Combination comb("PLAYER", {{Card(Rank::Two, Suit::Hearts),
                     Card(Rank::Two, Suit::Spades),
                     Card(Rank::Three, Suit::Diamonds),
                     Card(Rank::Three, Suit::Clubs),
                     Card(Rank::Three, Suit::Spades)}});
    // Count the number of ranks in the combination
    std::array<int, 13> ranks = combination.CountRanks();
    std::array<int, 13> ranks2 = comb.CountRanks();
    // Check that the counts are correct
    assert(ranks[0] == 1);   // rank 2 appears 1 times
    assert(ranks[1] == 0);   // rank 3 appears 0 times
    assert(ranks[2] == 1);   // rank 4 appears 1 time
    assert(ranks[3] == 0);   // rank 5 appears 0 times
    assert(ranks[4] == 1);   // rank 6 appears 1 time
    assert(ranks[5] == 0);   // rank 7 appears 0 times
    assert(ranks[6] == 1);   // rank 8 appears 1 time
    assert(ranks[7] == 0);   // rank 9 appears 0 times
    assert(ranks[8] == 1);   // rank 10 appears 1 time
    assert(ranks[9] == 0);   // rank J appears 0 times
    assert(ranks[10] == 0);  // rank Q appears 0 times
    assert(ranks[11] == 0);  // rank K appears 0 times
    assert(ranks[12] == 0);  // rank A appears 0 times
    assert(ranks2[0] == 2);   // rank 2 appears 2 times
    assert(ranks2[1] == 3);   // rank 3 appears 3 times
    assert(ranks2[2] == 0);   // rank 4 appears 0 time
    assert(ranks2[3] == 0);   // rank 5 appears 0 times
}


void testHandlePair() {
    vector<Card> fiveCards {
        {Two, Hearts},
        {Two, Spades},
        {Seven, Clubs},
        {Jack, Diamonds},
        {Ace, Hearts}
    };
    TieBreaker tie(PAIR, fiveCards);
    vector<Card> strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 4);
    assert(strongestCards[0].rank == Two);
    assert(strongestCards[1].rank == Ace);
    assert(strongestCards[2].rank == Jack);
}

// Test for High Card
void testHandleHighCard() {
    vector<Card> fiveCards {
        {Two, Hearts},
        {Five, Spades},
        {Seven, Clubs},
        {Jack, Diamonds},
        {Ace, Hearts}
    };
    TieBreaker tie(PAIR, fiveCards);
    vector<Card> strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 5);
    assert(strongestCards[0] == Card(Ace, Hearts));
    assert(strongestCards[1].rank == Jack);
    assert(strongestCards[2].rank == Seven);
    assert(strongestCards[3].suit == Spades);
    assert(strongestCards[4].rank == Two);
}

// Test for Two Pair
void testHandleTwoPair() {
    vector<Card> fiveCards {
        {Two, Hearts},
        {Two, Spades},
        {Seven, Clubs},
        {Seven, Diamonds},
        {Jack, Hearts}
    };
    TieBreaker tie(TWO_PAIR, fiveCards);
    vector<Card> strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 3);
    assert(strongestCards[0].rank == Seven);
    assert(strongestCards[1].rank == Two);
    assert(strongestCards[2].rank == Jack);

    fiveCards = {
        {Two, Hearts},
        {Two, Spades},
        {Seven, Clubs},
        {Nine, Diamonds},
        {Nine, Hearts}
    };
    tie = TieBreaker(TWO_PAIR, fiveCards);
    strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 3);
    assert(strongestCards[0].rank == Nine);
    assert(strongestCards[1].rank == Two);
    assert(strongestCards[2].rank == Seven);
}

// Test for Three of a Kind
void testHandleThreeOfAKind() {
    vector<Card> fiveCards {
        {Two, Hearts},
        {Two, Spades},
        {Two, Clubs},
        {Seven, Diamonds},
        {Jack, Hearts}
    };
    TieBreaker tie(THREE_OF_A_KIND, fiveCards);
    vector<Card> strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 1);
    assert(strongestCards[0].rank == Two);

    fiveCards = {
        {Ace, Hearts},
        {King, Spades},
        {King, Clubs},
        {King, Diamonds},
        {Nine, Hearts}
    };
    tie = TieBreaker(THREE_OF_A_KIND, fiveCards);
    strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 1);
    assert(strongestCards[0].rank == King);
    
}

// Test for Straight
void testHandleStraight() {
    vector<Card> fiveCards {
        {Two, Hearts},
        {Three, Spades},
        {Four, Clubs},
        {Five, Diamonds},
        {Six, Hearts}
    };
    TieBreaker tie(STRAIGHT, fiveCards);
    vector<Card> strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 5);
    assert(strongestCards[0].rank == Six);

    fiveCards = {
        {Ace, Hearts},
        {King, Spades},
        {Queen, Clubs},
        {Jack, Diamonds},
        {Ten, Hearts}
    };
    tie = TieBreaker(STRAIGHT, fiveCards);
    strongestCards = tie.determineStrongestCards(fiveCards);
    assert(strongestCards.size() == 5);
    assert(strongestCards[0].rank == Ace);
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
    //check if combinations length is 60
    assert(combinations.size() == 60);
    

    sort(combinations.begin(), combinations.end(), HandComparator::compareHands);
    //check if the vector is sorted according to rank values
    //use assert
    int middle = combinations.size()/2;
    //check if the first combination is equal or higher than some combinations in the middle
    assert(combinations[0].GetBestHandRank().rank >= combinations[middle].GetBestHandRank().rank);
    assert(combinations[0].GetBestHandRank().rank >= combinations[middle/2].GetBestHandRank().rank);
    assert(combinations[0].GetBestHandRank().rank >= combinations[combinations.size()-1].GetBestHandRank().rank);

}




int main() {
    testIsFlush();
    testIsStraightFlush();
    testIsFourOfAKind();
    testIsFullHouse();
    testIsRoyalFlush();
    testIsStraight();
    testCompareHands();
    testCountRanks();

    //tests on tiebreaker.cpp
    testHandlePair();
    testHandleHighCard();
    testHandleTwoPair();
    testHandleThreeOfAKind();
    testHandleStraight();


    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}


