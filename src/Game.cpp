//This class represents the actual game itself. 
//It should be able to manage the gameplay, including the different betting rounds, dealing of cards, and determining the winner(s) of each hand. 
//It should also keep track of the players, their current hands, and their current bets.
#include <iostream>
#include <string>
#include "..\Headers\Game.h" 

using namespace std;

Game::Game():num_players(0), currentPlayerIndex(0),deck(), pot(0), players(vector<Player>()), communityCards(vector<Card>())
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

void Game::run() {
    while(!isGameOver){
        //the deck is already shuffled when it is initialized.
        StartingRound();
        dealHoleCards();
        //is good
        bettingPreFlop();//is good
        if(isRoundOver)break;;
        dealFlop();//is good
        bettingPostFlopOrTurnOrRiver();
        if(isRoundOver)break;
        dealTurnOrRiver();
        bettingPostFlopOrTurnOrRiver();
        if(isRoundOver)break;
        dealTurnOrRiver();
        bettingPostFlopOrTurnOrRiver();
        if(isRoundOver)break;
        DetermineWinner();//hardest part
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
    communityCards.push_back(deck.dealCard());
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
        activePlayer->addChips(pot);
        pot = 0;
        isRoundOver=true;
        ResetRound();        
    }

}

void Game::bettingPreFlop(){
    int minimumBet = bigBlind; // the minimum bet is equal to the big blind
    bettingRound(minimumBet);
}

void Game::bettingPostFlopOrTurnOrRiver(){
    int minimumBet = 0; // minimum bet is now zero, because no bets have been made yet
    bettingRound(minimumBet);
}


void Game::bettingRound(int minimumBet) {
    int playerIndex = currentPlayerIndex; // starting player for the round
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
            Player& currentPlayer = players[(playerIndex + i+2) % num_players];

            // Skip the player if they've already folded
            if (!currentPlayer.isActive()) {
                continue;
            }
            // Prompt the player to make a decision
            cout << "Player " << currentPlayer.getName() << ", it's your turn to act." << endl;
            cout << "Your hand: "<<endl;
            currentPlayer.printHoleCards();
            cout << "The community cards are: " << endl;
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
                    cout << "How much do you want to raise?" << endl;                   
                    std::cin >> raiseAmount;

                    // Validate that the raise amount is at least the minimum raise
                    minimumRaise = minimumBet * 2 - currentPlayer.getCurrentBet(); // In poker, the minimum raise is typically double the previous bet or raise
                    if (raiseAmount < minimumRaise) {
                        cout << "Your raise must be at least " << minimumRaise << " chips." << endl;
                        i--; // Prompt the same player again
                        break;
                    }

                    // Place the raise and update the current bet and minimum bet
                    currentPlayer.bet(raiseAmount);
                    minimumBet = raiseAmount;
                    pot += raiseAmount;
                    playersToAct--; // The player who raised does not need to act again for now..
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
                        currentPlayer.bet(callAmount);
                        pot += callAmount;
                    } else {
                        cout << "You check." << endl;
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
    for(auto &player:players){
        if(player.isActive()){
            vector<Combination> playersHands = player.getCombinations();
            //append allHands with the vector playersHands
            allHands.insert(allHands.end(), playersHands.begin(), playersHands.end());
        }
    }
    //sort allHands with compareHands
    sort(allHands.begin(), allHands.end(), HandComparator::compareHands);
    //the first element in allHands is the best hand
    Combination bestHand = allHands[0];
    //the last element in allHands is the worst hand
    Combination worstHand = allHands[allHands.size()-1];
    //if the best hand is the same as the worst hand, then there is only one winner


}



//might gonna use 

void Game::ResetRound() {
    // Reset the deck
    // renew the deck
    deck = Deck();
    //shuffle the deck
    deck.shuffle();

    // Reset the pot
    pot = 0;

    // Reset the players and their hands
    for (int i = 0; i < num_players; i++) {
        Player& player = players[i];
        player.getHand().clearHand();
        player.Activate();
        if(player.getChips()<=0){//check if any player is out of chips
            player.Deactivate();
        }
    }
    isGameOver=EndGame();
    
    //increment the dealer=curentPlayerIndex
    currentPlayerIndex = (currentPlayerIndex + 1) % num_players;

    // Reset the community cards
    communityCards.clear();
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
