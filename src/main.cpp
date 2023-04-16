#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
#include "../Headers/Player.h"
#include "../Headers/Game.h"



int main()
{
	char con;
    Game game;
    int num_of_players= game.getNumPlayers();
	do{
	
	game.run();
    cout << endl;
    cout << endl;
    cout << endl;

	cout<<"Do you want to play again (y for yes, anything else for no): "<<endl;
	cin>>con;

	}while(con=='y' || con=='Y');

    return 0;
}
