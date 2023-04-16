#include "../Headers/Player.h"
#include "../Headers/Hand.h"
#include <iostream>

using namespace std;
Player::Player(string n, int c): name(n), chips(c), hand(Hand()){
    this->currentBet = 0;
    this->isactive=true; //at the beginning of the game, all players are active
}
void Player::printHoleCards() const{
    for (int i = 0; i < 4; i++) {
        cout << hand.getCards()[i].toString() << "  ";
    }
    cout << '\n';
}
void Player::receiveHoleCard(Card card){
    hand.addPlayerCard(card);
}
void Player::receiveCommunityCard(Card card){
    hand.addCommunityCard(card);
}
void Player::bet(int amount){
    if(amount > chips){
        amount = chips;
        cout<< "You don't have enough chips to bet that much. Betting all chips."<<endl;
    }
    chips -= amount;
    currentBet += amount;
    
}
int Player::getCurrentBet() const{
    return currentBet;
}
void Player::ResetCurrentBet(){
    currentBet = 0;
}
Hand Player::getHand() const{
    return hand;
}
string Player::getName() const {
    return name;
}
int Player::getChips() const {
    return chips;
}
void Player::addChips(int amount) {
    chips += amount;
}
void Player::subtractChips(int amount) {
    chips -= amount;
}
bool Player::isActive() const {
    return isactive;
}
void Player::fold() {
    isactive = false;
}
vector<Combination> Player::getCombinations() const{
    return hand.getCombinations(this->name);
}
void Player::Deactivate(){
    isactive = false;
}
void Player::Activate(){
    isactive = true;
}
