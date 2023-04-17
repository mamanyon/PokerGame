#include "../Headers/Combination.h"
#include "../Headers/Hand.h"
#include <algorithm>
#include <iostream>


Combination::Combination(string name, vector<Card> fiveCards): name(name), fiveCards(fiveCards) {
    tieBreaker = GetBestHandRank();
    

}
std::array<int, 13> Combination::CountRanks() const {
    std::array<int, 13> ranks{};
    for (const auto& card : fiveCards) {
        ranks[card.rank - 2]++;
    }
    return ranks;
}

bool Combination::IsPair() const {
    //check if there is a pair in the five cards
    for (int i = 0; i < fiveCards.size(); i++) {
        for (int j = i + 1; j < fiveCards.size(); j++) {
            if (fiveCards[i].rank == fiveCards[j].rank) {
                return true;
            }
        }
    }
    return false;
}
bool Combination::IsTwoPair() const {
    //check if there is two different pairs in the five cards
    auto rankCount = CountRanks();
    int numPairs = 0;
    for (const auto& count : rankCount) {
        if (count == 2) {
            numPairs++;
        }
    }
    return (numPairs == 2);
}

bool Combination::IsThreeOfAKind() const {
    //check if there is three cards of the same rank in the five cards
    auto rankCount = CountRanks();
    for (const auto& count : rankCount) {
        if (count == 3) {
            return true;
        }
    }
    return false;
}

bool Combination::IsFullHouse() const {
    //check if there is a pair and a three of a kind in the five cards
    auto rankCount = CountRanks();
    bool hasPair = false;
    bool hasThreeOfAKind = false;
    for (const auto& count : rankCount) {
        if (count == 2) {
            hasPair = true;
        }
        else if (count == 3) {
            hasThreeOfAKind = true;
        }
    }
    return (hasPair && hasThreeOfAKind);
}
bool Combination::IsFourOfAKind() const {
    //check if there is four cards of the same rank in the five cards
    auto rankCount = CountRanks();
    for (const auto& count : rankCount) {
        if (count == 4) {
            return true;
        }
    }
    return false;
}
bool Combination::IsStraight() const {
    //check if there is a straight.
    //store five cards in a vector and then sort the vector ascending 
    vector<Card> sortedFiveCards = fiveCards;
    sort(sortedFiveCards.begin(), sortedFiveCards.end(), [](const Card& a, const Card& b) {
        return a.rank < b.rank;
    });
    // Check for a straight starting from Ace (A, 2, 3, 4, 5)
    if (sortedFiveCards[0].rank == 2 && sortedFiveCards[1].rank == 3 &&
        sortedFiveCards[2].rank == 4 && sortedFiveCards[3].rank == 5 &&
        sortedFiveCards[4].rank == 14) {
        return true;
    }
    //check if the difference between the ranks of the cards is 1
    for (int i = 0; i < sortedFiveCards.size() - 1; i++) {
        if (sortedFiveCards[i + 1].rank - sortedFiveCards[i].rank != 1) {
            return false;
        }
    }
    return true;
}
bool Combination::IsFlush() const {
    //check if there is a flush
    for (int i = 0; i < fiveCards.size() - 1; i++) {
        if (fiveCards[i].suit != fiveCards[i + 1].suit) {
            return false;
        }
    }
    return true;
}
bool Combination::IsStraightFlush() const {
    //check if there is a straight flush
    return (IsStraight() && IsFlush());
}
bool Combination::IsRoyalFlush() const {
    //check if there is a royal flush
    return (IsStraightFlush() && fiveCards[0].rank == 10);
}

TieBreaker Combination::GetBestHandRank() const {
    //return an object of tiebreaker according to the rank of the hand
    if (IsRoyalFlush()) {
        TieBreaker royalFlush(ROYAL_FLUSH, fiveCards);
        return royalFlush;
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

void Combination::PrintHand() const {
    //print the five cards of the hand
    for (int i = 0; i < fiveCards.size(); i++) {
        std::cout << fiveCards[i].toString() << "  ";
    }
    std::cout << std::endl;
}