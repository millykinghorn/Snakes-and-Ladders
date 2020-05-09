//Final Project Milly Kinghorn 07/05/20
//This header file declares global parameters, global functions, and classes

#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <iostream>

using namespace std;

/*-------GAME PARAMETERS---------*/

static int snake_length = 5; //moves player 5 spaces back
static int ladder_length = 5; //moves player 5 spaces on
static int min_rows = 2;
static int max_rows = 20;
static int min_cols = 2;
static int max_cols = 20;
static int min_players = 1;
static int max_players = 6;

/*-------GLOBAL FUNCTIONS---------*/

int roll_dice();
bool integer_check(string val, int min, int max);

/*---------CLASSES----------------*/

//generic tile class is overwritten by snake and ladder classes
class tile {
protected:
	int number{};
	string occupied{}; //reperesented by initial of the player on the tile
	string type{};
public:
	tile() = default;
	~tile() {};

	void set_number(int i);
	int get_number();
	void set_occupance(string x);
	string get_occupied();
	void set_type(string s);
	string get_type();
};

//snake is a type of tile with a start and end point
class snake : public tile {
protected:
	int number;
	int snake_start;
	int snake_end;
	string occupied;
	string type;
public:
	snake() = default;
	snake(int snake_start_, int snake_end_) :
		number{ snake_start_ }, snake_start(snake_start_), snake_end{ snake_end_ }, occupied{ " " }, type{ "snake" }{};
	~snake() {};

	int get_snake_start();
	int get_snake_end();
};

//ladder is a type of tile with a start and end point
class ladder :tile {
protected:
	int number;
	int ladder_start;
	int ladder_end;
	string occupied;
	string type;
public:
	ladder() = default;
	ladder(int ladder_start_, int ladder_end_) :
		number{ ladder_start_ }, ladder_start(ladder_start_), ladder_end{ ladder_end_ }, occupied{ " " }, type{ "ladder" }{};
	~ladder() {};

	int get_ladder_start();
	int get_ladder_end();
};

//board is an array of tiles with size of rows * columns
class board : public tile {
protected:
	int rows;
	int columns;
	int size;
	tile* tiles{ nullptr };

public:
	board() { rows = 0, columns = 0, size = 0; }
		//rows{}, columns{}, size{}{};
	board(int rows_, int columns_) :
		rows{ rows_ }, columns{ columns_ }, size{ rows_ * columns_ } {
		tiles = new tile[size];
		for (int i{}; i < size; i++) {
			tiles[i].set_number(i + 1);
			occupance(i, " ");
			tiles[i].set_type("normal");
		}

		//Algorithm for auto inserting snakes and ladders; 
		int number_of_snakes = (size - size % 12) / 12; //e.g. for 6x6 board, 3 snakes and 3 ladders
		int number_of_ladders = (size - size % 12) / 12;
		
		//snake every 10 tiles working back from second to last tile
		for (size_t i{}, temp = number_of_snakes; i < temp; i++) {
			int tile_number = size - 1 - (i * 10);
			tiles[tile_number - 1].set_type("snake");
		}

		//ladder every 10 tiles working forward from second tile
		for (size_t i{}, temp = number_of_ladders; i < temp; ++i) {
			int tile_number = 2 + (i * 10);
			tiles[tile_number-1].set_type("ladder");
		}

		//overwrite original tiles of type snake or ladder
		for (size_t i{}, temp=size; i < temp; i++) {
			if (tiles[i].get_type() == "snake") {
				tiles[i] = snake(i + 1, i + 1 - snake_length);
				tiles[i].set_number(i + 1);
				tiles[i].set_occupance(" ");
				tiles[i].set_type("snake");
				std::cout << "snake from " << i + 1 << " to " << i + 1 - snake_length << endl;
			}
			else if (tiles[i].get_type() == "ladder") {
				tiles[i] = snake(i + 1, i + 1 + ladder_length);
				tiles[i].set_number(i + 1);
				tiles[i].set_occupance(" ");
				tiles[i].set_type("ladder");
				std::cout << "ladder from " << i + 1 << " to " << i + 1 + ladder_length << endl;
			}
		}
		occupance(0, "x"); //first tile is occupied
	};

	~board() { std::cout << "Game Over"; };

	void display();
	void occupance(int i, string s);
	int get_size();
	string get_type(int i);
};


class player : public board {
protected:
	string name;
	string initial;
	int position;
public:
	player() :
		name{ "player" }, position{ 1 }{};

	player(string name_) :
		name{ name_ } {
		set_position(1);
		initial = name_;
		for (size_t i{}; i < name_.length() - 1; i++) {
			initial.pop_back();
		}
	};

	string get_name();
	string get_initial();
	void set_position(int i);
	int get_position();
	bool on_board_check(board& b);;

	void move(board& b);
	void snake_move(board& b, snake& s);
	void ladder_move(board& b, ladder& l);
};

#endif