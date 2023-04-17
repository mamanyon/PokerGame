//This class represents the actual game itself. 
//It should be able to manage the gameplay, including the different betting rounds, dealing of cards, and determining the winner(s) of each hand. 
//It should also keep track of the players, their current hands, and their current bets.
#include <iostream>
#include <chrono>   // for std::chrono::seconds and std::this_thread::sleep_for
#include <thread>   // for std::this_thread::sleep_for
#include <string>
#include "..\Headers\Game.h" 

using namespace std;

Game::Game():num_players(0), currentPlayerIndex(0), pot(0)
{
    this->isGameOver = false;
    this->isRoundOver = false;
    cout << "Welcome to the game of Omaha Hi/Lo!" << endl;
    cout << "How many players are there?" << endl;

    int numPlayers,startingMoney;
    std::cin >> numPlayers;
    this->num_players = numPlayers;

    cout << "How much money does each player start with?" << endl;
    std::cin >> startingMoney;
    for (int i = 0; i < numPlayers; i++) {
        cout << "What is the name of player " << i + 1 << "?" << endl;
        string name;
        std::cin >> name;
        Player p(name, startingMoney);   
        players.push_back(p);
    }
    
}
int Game::getNumPlayers() const{
    return num_players;
}
void Game::CheckWhoIsOut(){
    //if there are players with 0 chips, they are out of the game
    //erase them from the players vector
    //and update the number of players
    for(int i=0;i<players.size();i++){
        if(players[i].getChips()==0){
            cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;
            //The player is out of the game
            cout<<players[i].getName()<<" is out of the game."<<endl;
            cout<<"thanks for playing!"<<endl;
            cout<<""<<endl;cout<<""<<endl;cout<<""<<endl;
            players[i].fold();
            players.erase(players.begin()+i);
        }
    }
    num_players=players.size();
}
void Game::run() {
    while(!isGameOver){
        while(!isRoundOver){
            CheckWhoIsOut();
            StartingRound();
            dealHoleCards();
            //is good
            bettingPreFlop();//is good
            cout<<"___________________________________"<<endl;
            if(isRoundOver)break;;
            dealFlop();//is good
            bettingPostFlopOrTurnOrRiver();
            cout<<"___________________________________"<<endl;
            if(isRoundOver)break;
            dealTurnOrRiver();
            bettingPostFlopOrTurnOrRiver();
            cout<<"___________________________________"<<endl;
            if(isRoundOver)break;
            dealTurnOrRiver();
            bettingPostFlopOrTurnOrRiver();
            cout<<"___________________________________"<<endl;
            if(isRoundOver)break;
            DetermineWinner();
        }
     }
}

void Game::printCommunityCards() const{
    if(communityCards.size() > 0){
    cout << "The community cards are: "<<endl;
        for(Card c: communityCards){
            cout<<c.toString()<<" ";
        }
        cout<<'\n';
    }
    else{
        cout<<"No community cards have been dealt yet."<<endl;
    }
}

void Game::StartingRound(){
    // First player pays the pot minimum bet
    Player& firstPlayer = players[currentPlayerIndex];
    //if the player doesnt have chips- he is out of the game

    cout << "Player " << firstPlayer.getName() << ", you need to pay the pot minimum bet of " << smallBlind << "." << endl;
    firstPlayer.bet(smallBlind);
    pot += smallBlind;

    // Second player pays the big blind
    int playerIndex = (currentPlayerIndex + 1) % num_players;
    Player& secondPlayer = players[playerIndex];
    cout << "Player " << secondPlayer.getName() << ", you need to pay the big blind of " << bigBlind << "." << endl;
    secondPlayer.bet(bigBlind);
    pot += bigBlind;  
}

void Game::dealHoleCards() {//deal 4 cards to each player at the beginning of the game
//starting from the player that pays the small blind- left to dealer = playerIndex
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < num_players; j++) {
            Player& player = players[(currentPlayerIndex + j) % num_players];
            player.receiveHoleCard(deck.dealCard());
        }
    }
}

void Game::dealFlop() {
    //throw away the first card
    deck.dealCard();
    //deal 3 cards to the community cards
    vector<Card> cards;
    
    for(int i = 0; i < 3; i++){
        Card c=deck.dealCard();
        cards.push_back(c);
        for (Player& player : players) {  
            player.receiveCommunityCard(c);
        }
    }
    
    //add the 3 cards to the community cards
    communityCards.insert(communityCards.end(), cards.begin(), cards.end());

}

void Game::dealTurnOrRiver() {
    //throw away the first card
    deck.dealCard();
    //deal 1 card to the community cards
    Card c=deck.dealCard();
    communityCards.push_back(c);
    //for each player 
    for (Player& player : players) {  
            player.receiveCommunityCard(c);
    }
}

void Game::checkForWinner(){
    //check if there is only one player left
    int numActivePlayers = 0;
    Player* activePlayer = nullptr;
    for (Player& player : players) {
        if (player.isActive()) {
            numActivePlayers++;
            activePlayer = &player;
        }
    }
    if(numActivePlayers==1){
        //if there is only one player left, he is the winner of the round
        cout << "Player " << activePlayer->getName() << " wins the round!" << endl;
        cout << "You won" << pot << " chips!" << endl;
        activePlayer->addChips(pot);
        isRoundOver=true;
        ResetRound();        
    }

}

void Game::bettingPreFlop(){
    int minimumBet = bigBlind; // the minimum bet is equal to the big blind
    bettingRound(minimumBet);
    //current bet set to 0 for the next round for each player
    for (Player& player : players) {
        player.SetCurrentBet(0);
    }
    
}

void Game::bettingPostFlopOrTurnOrRiver(){
    int minimumBet = 0; // minimum bet is now zero, because no bets have been made yet
    bettingRound(minimumBet);
}


void Game::bettingRound(int minimumBet) {
    int playerIndex = currentPlayerIndex; // starting player for the round
    if(minimumBet==10){//if it is the first round, the starting player is the player that after the big blind
        playerIndex = (currentPlayerIndex + 2) % num_players;
    }//otherwise, the starting player is the player that before the small blind
    int playersToAct = 0; // number of active players who have not yet checked or folded
    for (Player& player : players) {//count the number of active players
        if (player.isActive()) {
            playersToAct++;
        }
    }
    // Prompt each player to make a bet or fold
    bool roundFinished = false;
    int i=0;
    while (!roundFinished) {  
            if(playersToAct==0){ //if all players have checked, called or folded
                roundFinished=true;
                break;
            }
            Player& currentPlayer = players[(playerIndex + i) % num_players];

            // Skip the player if they've already folded
            if (!currentPlayer.isActive()) {
                continue;
            }
            cout<<" "<<endl;
            // Prompt the player to make a decision
            cout << "Player " << currentPlayer.getName() << ", it's your turn to act." << endl;
            cout << "Your hand: "<<endl;
            currentPlayer.printHoleCards();
            printCommunityCards();
            cout << "The minimum bet is " << minimumBet << ". You have " << currentPlayer.getChips() << " chips." << endl;
            cout <<"Your current bet in this round is "<<currentPlayer.getCurrentBet()<<endl;
            cout << "Do you want to (1) raise, (2) fold, or (3) check/call?" << endl;

            int choice;
            std::cin >> choice;
            int callAmount;
            int minimumRaise;
            int raiseAmount;
            switch (choice) {
                case 1: // raise
                //if the player doesnt have chips to raise, he can only call
                    if(currentPlayer.getChips()<minimumBet){
                        cout<<" "<<endl;
                        cout<<"You dont have enough chips to raise. You can only call."<<endl;
                        cout<<" "<<endl;
                        callAmount = minimumBet - currentPlayer.getCurrentBet();
                        currentPlayer.bet(callAmount);
                        pot += callAmount;
                        playersToAct--;
                        break;
                    }
                    cout << "How much do you want to raise?" << endl;                   
                    std::cin >> raiseAmount;
                    cout<<" "<<endl;

                    // Validate that the raise amount is at least the minimum raise
                    minimumRaise = minimumBet * 2 - currentPlayer.getCurrentBet(); // In poker, the minimum raise is typically double the previous bet or raise
                    if (raiseAmount < minimumRaise) {
                        cout<<" "<<endl;
                        cout << "Your raise must be at least " << minimumRaise << " chips." << endl;
                        cout<<" "<<endl;

                        i--; // Prompt the same player again
                        break;
                    }

                    // Place the raise and update the current bet and minimum bet
                    minimumBet = raiseAmount+ currentPlayer.getCurrentBet();
                    currentPlayer.bet(raiseAmount);
                    pot += raiseAmount;
                    playersToAct--; // The player who raised does not need to act again for now..
                    //but the other players that are still active need to act again
                    for(Player& player:players){
                        if(player.isActive()){
                            playersToAct++;
                        }
                    }
                    playersToAct--; //..except for the player who raised
                    break;

                case 2: // Fold
                    cout << "You fold." << endl;
                    currentPlayer.fold();
                    playersToAct--;
                    checkForWinner();
                    if(isRoundOver)
                        return;
                    break;

                case 3: // Check/Call
                    callAmount = minimumBet - currentPlayer.getCurrentBet();
                    if (callAmount > 0) {
                        cout << "You call " << callAmount << "." << endl;
                        cout<<""<<endl;
                        currentPlayer.bet(callAmount);
                        pot += callAmount;
                    } else {
                        cout << "You check." << endl;
                        cout<<""<<endl;
                    }
                    playersToAct--;
                    break;

                default: // Invalid choice
                    cout << "Invalid choice. Please choose 1, 2, or 3." << endl;
                    i--; // Prompt the same player again
                    break;
            }
            i++;
        }
}



void Game::DetermineWinner() {
    //Determine the best hand for each player that is still active
    //also determine the worst hand for each player that is still active
    vector<Combination> allHands ;
    cout<<"Determining the winner..."<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    for(auto &player:players){
        if(player.isActive()){
            vector<Combination> playersHands = player.getCombinations();
            //append allHands with the vector playersHands
            allHands.insert(allHands.end(), playersHands.begin(), playersHands.end());
        }
    }
    //print size all hands for testing
    cout<<"Size of all hands: "<<allHands.size()<<endl;
    //sort allHands with compareHands
    sort(allHands.begin(), allHands.end(), HandComparator::compareHands);
    cout<<"__________________________________________________________" <<endl;
    cout<<"__________________________________________________________" <<endl;
    cout<<"__________________________________________________________" <<endl;
    cout<<"__________________________________________________________" <<endl;
    //the first element in allHands is the best hand
    Combination bestHand = allHands[0];
    //the last element in allHands is the worst hand
    Combination worstHand = allHands[allHands.size()-1];
    //the player with the best hand wins half of the pot
    cout<<"The player with the best hand is: "<<bestHand.name<<endl;
    cout<<"with the hand: "<<endl; 
    bestHand.PrintHand();
    cout<<"The player with the worst hand is: "<<worstHand.name<<endl;
    cout<<"with the hand: "<<endl;
    worstHand.PrintHand();
    if(bestHand.name==worstHand.name){
        cout<<"Player "<<bestHand.name<<" wins the whole pot, " << pot <<"chips !!!" <<endl;
        SearchPlayerByName(bestHand.name)->addChips(pot);
    }else{
        cout<<"Player "<<bestHand.name<<" wins half of the pot, " << (pot/2) << "chips !" <<endl;
        cout<<"Player "<<worstHand.name<<" wins half of the pot, "<< (pot/2) << "chips !" <<endl;
        SearchPlayerByName(bestHand.name)->addChips(pot/2);
        SearchPlayerByName(worstHand.name)->addChips(pot/2);
    }
    cout<<"The Round is over!"<<endl;
    cout<<"___________________________________"<<endl;
    cout<<"___________________________________"<<endl;
    cout<<"___________________________________"<<endl;
    cout<<"Starting a new round..."<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    isRoundOver=true;
    ResetRound();
}
Player* Game::SearchPlayerByName(string name){
    for(auto &player:players){
        if(player.getName()==name){
            return &player;
        }
    }
    return nullptr;
}




void Game::ResetRound() {
    // Reset the deck
    // renew the deck and shuffle it
    deck = Deck();
    

    // Reset the pot
    pot = 0;

    // Reset the players and their hands
    for (int i = 0; i < num_players; i++) {
        Player& player = players[i];
        player.getHand().clearHand();
        player.ResetCurrentBet();
        player.Activate();
        if(player.getChips()<=0){//check if any player is out of chips
            player.Deactivate();
        }
    }
    isGameOver=EndGame();
    
    //increment the dealer=curentPlayerIndex
    currentPlayerIndex = (currentPlayerIndex + 1) % num_players;
    isRoundOver=false;
    // Reset the community cards
    communityCards.clear();
    cout<<""<<endl;
    cout<<".........................................."<<endl;
    cout<<"New Round Started!"<<endl;
}

bool Game::EndGame() {
    // Check if there is only one active player left
    int activePlayers = 0;
    Player* winner = nullptr;
    for (int i = 0; i < num_players; i++) {
        if (players[i].isActive()) {
            activePlayers++;
            winner = &players[i];
        }
    }
    if (activePlayers == 1) {
        cout << "There's only one active player left. " << endl;
        cout << winner->getName()<< "You have won the game!" << endl;
        cout << "Congratulations!" << endl;
        cout << "Thank you for playing!" << endl;
        cout << "   " << endl;
        cout << "Goodbye!" << endl;

        isGameOver=true;
        return true;
    }
    return false;
}
