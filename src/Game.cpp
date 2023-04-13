//This class represents the actual game itself. 
//It should be able to manage the gameplay, including the different betting rounds, dealing of cards, and determining the winner(s) of each hand. 
//It should also keep track of the players, their current hands, and their current bets.
#include <iostream>
#include <string>
#include "..\Headers\Game.h" 
using namespace std;

Game::Game():num_players(0), currentPlayerIndex(0),deck(Deck()), pot(0), players(vector<Player>()), communityCards(vector<Card>())
{
    this->isGameOver = false;
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

void Game::run(int startingPlayerIndex) {
     this->currentPlayerIndex=startingPlayerIndex;
    //the deck is already shuffled when it is initialized.
    StartingRound();
    dealHoleCards();
    //is good
    bettingPreFlop();//is good
    if(isGameOver)return;
    dealFlop();//is good
    bettingPostFlopOrTurnOrRiver();
    if(isGameOver)return;
    dealTurnOrRiver();
    bettingPostFlopOrTurnOrRiver();
    if(isGameOver)return;
    dealTurnOrRiver();
    bettingPostFlopOrTurnOrRiver();
    if(isGameOver)return;
    determineWinner();//hardest part
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
    cout << "Player " << firstPlayer.getName() << ", you need to pay the pot minimum bet of " << minimumBet << "." << endl;
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
        //if there is only one player left, he is the winner
        cout << "Player " << activePlayer->getName() << " wins the round!" << endl;
        activePlayer->addChips(pot);
        pot = 0;
        isGameOver=true;
        //resetGame();
        
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

            switch (choice) {
                case 1: // raise
                    cout << "How much do you want to raise?" << endl;
                    int raiseAmount;
                    std::cin >> raiseAmount;

                    // Validate that the raise amount is at least the minimum raise
                    int minimumRaise = minimumBet * 2 - currentPlayer.getCurrentBet(); // In poker, the minimum raise is typically double the previous bet or raise
                    if (raiseAmount < minimumRaise) {
                        cout << "Your raise must be at least " << minimumRaise << " chips." << endl;
                        i--; // Prompt the same player again
                        continue;
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
                    if(isGameOver)
                        return;
                    break;

                case 3: // Check/Call
                    int callAmount = minimumBet - currentPlayer.getCurrentBet();
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
                    continue;
            }
            i++;
        }
}



void Game::determineWinner() {
    //Determine the best hand for each player that is still active
    //also determine the worst hand for each player that is still active
    //i want to compare between every 2 players that are still active
    //and determine who has the best hand
    //after that - determine who has the worst hand
    //the player with the best hand wins half of the pot
    //the player with the worst hand wins the other half of the pot
    
}



//might gonna use 

void Game::resetGame() {
    // Reset the deck
    deck.reset();

    // Reset the pot and current bet
    pot = 0;
    currentBet = 0;

    // Reset the players
    for (int i = 0; i < num_players; i++) {
        Player& player = players[i];
        player.reset();
        player.deactivate();
    }

    // Activate the required number of players
    for (int i = 0; i < num_players; i++) {
        players[i].activate();
    }

    // Randomly select the first player to act
    currentPlayerIndex = rand() % num_players;

    // Reset the community cards
    communityCards.clear();
}



void Game::endGame() {
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
        cout << "There's only one active player left. " << winner->getName() << " wins!" << endl;
        winner->winChips(pot);
        pot = 0;
        return;
    }

    // Evaluate each player's hand and find the winner(s)
    vector<Player*> winners;
    Hand bestHand;
    for (int i = 0; i < num_players; i++) {
        if (!players[i].isActive()) {
            continue;
        }

        Hand currentHand = evaluateHand(players[i].getHoleCards(), communityCards);
        int comparison = compareHands(currentHand, bestHand);
        if (comparison > 0) {
            winners.clear();
            winners.push_back(&players[i]);
            bestHand = currentHand;
        } else if (comparison == 0) {
            winners.push_back(&players[i]);
        }
    }

    // Award the pot to the winner(s)
    if (winners.size() == 1) {
        Player* winner = winners[0];
        cout << "The winner is " << winner->getName() << " with ";
        printHandType(bestHand.getHandType());
        cout << "!" << endl;
        winner->winChips(pot);
    } else {
        cout << "There's a tie between ";
        for (int i = 0; i < winners.size(); i++) {
            cout << winners[i]->getName();
            if (i < winners.size() - 2) {
                cout << ", ";
            } else if (i == winners.size() - 2) {
                cout << " and ";
            }
        }
        cout << " with ";
        printHandType(bestHand.getHandType());
        cout << "!" << endl;
        int splitPot = pot / winners.size();
        for (int i = 0; i < winners.size(); i++) {
            winners[i]->winChips(splitPot);
        }
    }

    // Reset the players' hands and bets
    for (int i = 0; i < num_players; i++) {
        players[i].resetHand();
        players[i].resetCurrentBet();
    }
    communityCards.clear();
    pot = 0;
    currentPlayerIndex = dealerIndex;
}
