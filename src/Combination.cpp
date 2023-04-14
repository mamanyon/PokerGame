#include "Combination.h"
#include "Hand.h"

Combination::Combination(string name, vector<Card> fiveCards): name(name), fiveCards(fiveCards) {
    tieBreaker = GetBestHandRank();
    

}

bool Combination::IsRoyalFlush() const {
    //TODO
}
TieBreaker Combination::GetBestHandRank() const {
    //return an object of tiebreaker according to the rank of the hand
    if (IsRoyalFlush()) {
        return TieBreaker(ROYAL_FLUSH, &fiveCards);
    }
    else if (IsStraightFlush()) {
        return TieBreaker(STRAIGHT_FLUSH, fiveCards);
    }
    else if (IsFourOfAKind()) {
        return TieBreaker(FOUR_OF_A_KIND, fiveCards);
    }
    else if (IsFullHouse()) {
        return TieBreaker(FULL_HOUSE, fiveCards);
    }
    else if (IsFlush()) {
        return TieBreaker(FLUSH, fiveCards);
    }
    else if (IsStraight()) {
        return TieBreaker(STRAIGHT, fiveCards);
    }
    else if (IsThreeOfAKind()) {
        return TieBreaker(THREE_OF_A_KIND, fiveCards);
    }
    else if (IsTwoPair()) {
        return TieBreaker(TWO_PAIR, fiveCards);
    }
    else if (IsPair()) {
        return TieBreaker(PAIR, fiveCards);
    }
    else {
        return TieBreaker(HIGH_CARD, fiveCards);
    }
    
    
}