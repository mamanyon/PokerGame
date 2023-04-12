#include "../Headers/Comparator.h"
using namespace std;
int Comparator::compareHands(const Hand& hand1, const Hand& hand2) {
    const vector<Card>& cards1 = hand1.getCards();
    const vector<Card>& cards2 = hand2.getCards();

    // Check for royal flush
    if(isRoyalFlush(cards1))
        return 1;

}

bool Comparator::isRoyalFlush(const vector<Card>& cards) {
    // Check for royal flush
    if(isStraightFlush(cards)) {
        if(cards[0].rank == 14)
            return true;
    }
    return false;
}

bool Comparator::isStraightFlush(const vector<Card>& cards) {
    // Check for straight flush
    if(isFlush(cards)) {
        if(isStraight(cards))
            return true;
    }
    return false;
}
bool Comparator::isFlush(const vector<Card>& cards) {
    // Check for flush
    for(int i = 1; i < cards.size(); i++) {
        if(cards[i].suit != cards[i-1].suit)
            return false;
    }
    return true;
}
    