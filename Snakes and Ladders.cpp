// Snakes and Ladders.cpp
//Final Project Milly Kinghorn 07/05/20
//This program simulates the board game "snakes and ladders" for any players (within a range) on a board of any size (within a range)
//Class structure and global game parameters declared in Header.H
//Functions definitions- global and class- in Function_definitions.cpp

#include <ctime>
#include <random>
#include <list>
#include "Header.h" //contains iostream and string


int main()
{
	srand((unsigned)time(NULL)); //Seed for dice roll to be random

/*--------------SET UP THE BOARD---------------*/

	//Enter the size of the board via cin:
	string rows_input, columns_input;
	std::cout << "Board Set Up Options: " << endl;

	//Determine number of rows on board: edit max and min values at top of cpp file
	std::cout << "  No. Rows: ";
	cin >>  rows_input;
	while (integer_check(rows_input, min_rows,max_rows)==false){
		std::cout << "Please enter number between " <<min_rows<<" and " << max_rows<<" : ";
		cin >> rows_input;
	}
	int num_rows = stoi(rows_input);

	//Determine number of columns on board: edit max and min values at top of cpp file
	std::cout << "  No. Cols: ";
	cin >> columns_input;
	while (integer_check(columns_input, min_cols, max_cols) == false) {
		std::cout << "Please enter number between " << min_cols << " and " << max_cols << " : ";
		cin >> columns_input;
	}
	int num_cols = stoi(columns_input);

	board gameboard(num_rows, num_cols);

/*----------------SET UP PLAYERS-----------------*/

	string  players_input;
	std::cout << "How many players are playing? ";
	cin >> players_input;
	while (integer_check(players_input, min_players, max_players) == false) {
		std::cout << "Please enter number between " << min_players << " and " << max_players << " : ";
		cin >> players_input;
	}
	int num_players = stoi(players_input);

	//create list of players to iterate through when playing game
	list<player*> player_list;
	list<player>::iterator it;

	//add players to the list
	for (int i{}; i < num_players; i++) {
		string playername;
		std::cout << "Name of player " << i + 1 << ": ";
		cin >> playername;
		player* p = new player(playername);
		player_list.push_back(p);
		cin.ignore();
	}

	//check names of players
	cout << "Players:";
	for (auto it = player_list.cbegin(); it != player_list.cend(); it++) {
		string name = (*it)->get_name();
		std::cout << " " << name <<",";
	}
	cout << endl;

/*-------------------START GAME---------------*/

	std::cout << "Here is the board set up. = stands for ladder, ~ stands for snake. \n All players start at tile 1." << endl;
	gameboard.display();

	std::cout << endl;

	bool loop_until_break = true; //only break game loop when player goes out of scope

	while (loop_until_break == true) {
		for (auto it = player_list.cbegin(); it != player_list.cend(); it++) {

			string temp;
			std::cout << "Press enter for " << (*it)->get_name() << " to roll the dice" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			(*it)->move(gameboard);
			gameboard.display();
			std::cout << (*it)->get_name() << " is at square " << (*it)->get_position() << " a " << gameboard.get_type((*it)->get_position()) << " tile" << endl;

			//if on a snake tile, go to end of snake
			if (gameboard.get_type((*it)->get_position()) == "snake") {
				int snake_start = (*it)->get_position(); //instantiate snake
				snake s1 = snake((*it)->get_position(), ((*it)->get_position() - snake_length));
				(*it)->snake_move(gameboard, s1);
			}
			//if land on ladder, go to end of ladder
			else if (gameboard.get_type((*it)->get_position()) == "ladder") {
				int ladder_start = (*it)->get_position(); //instantiate ladder
				ladder l1 = ladder((*it)->get_position(), ((*it)->get_position() + ladder_length));
				(*it)->ladder_move(gameboard, l1);
			}

			std::cout << endl;
			std::cout << endl;

			//check player is still on board, if not, player has won
			if ((*it)->on_board_check(gameboard) == false) {
				std::cout << (*it)->get_name() << " won!" << endl;
				loop_until_break = false;
				break;
			}
			
		}
	}

	return 0;
}
