#include "HandComparator.h"


int HandComparator::compareHands(Combination &hand1, Combination &hand2) {
    //Determine the best hand for each instance of the hand class.
    HandRank rank1 = hand1.tieBreaker.rank;
    HandRank rank2 = hand2.tieBreaker.rank;
    if (rank1 > rank2) {
        return 1;
    }
    else if (rank1 < rank2) {
        return -1;
    }
    else{
        return hand1.tieBreaker.Compare(hand2.tieBreaker);
    }


}
