#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Hand.h"
#include <vector>

class Comparator {
    public:
        // Returns 1 if hand1 is better than hand2, -1 if hand2 is better than hand1, and 0 if they are equal
        static int comapreHands(const Hand& hand1, const Hand& hand2);
    private:
        //helper functions to determine hand type and compare hands
        static bool isRoyalFlush(const std::vector<Card>& cards);
        static bool isStraightFlush(const std::vector<Card>& cards);
        static std::vector<int> isFourOfAKind(const std::vector<Card>& cards);
        static std::vector<int> isFullHouse(const std::vector<Card>& cards);
        static bool isFlush(const std::vector<Card>& cards);
        static bool isStraight(const std::vector<Card>& cards);
        static std::vector<int> isThreeOfAKind(const std::vector<Card>& cards);
        static std::vector<int> isTwoPair(const std::vector<Card>& cards);
        static std::vector<int> isPair(const std::vector<Card>& cards);
        
        // Helper function to compare high cards
        static int compareHighCards(const std::vector<Card>& cards1, const std::vector<Card>& cards2, int excludeValue = -1, int excludeValue2 = -1);
}

#endif