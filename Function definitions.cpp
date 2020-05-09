//Final Project Milly Kinghorn 07/05/20
//This cpp file defines global functions and member functions of each class

#include "Header.h" //includes iostream and string

/*GLOBAL FUNCTION DEFINITIONS*/
int roll_dice() {
	return rand() % 6 + 1;
}

bool integer_check(string val, int min, int max) {
	for (int i{}, temp = val.length(); i < temp; i++) {
		if (isdigit(val[i]) == false) { return false; }
	}
	return (stoi(val) <= max && stoi(val) >= min) ? true : false;
}

/*TILE FUNCTION DEFINITIONS*/
void tile::set_number(int i) { number = i; }
int tile::get_number() { return number; }
void tile::set_occupance(string x) { occupied = x; }
string tile::get_occupied() { return occupied; }
void tile::set_type(string s) { type = s; }
string tile::get_type() { return type; }

/*SNAKE FUNCTION DEFINITIONS*/
int snake::get_snake_start() { return snake_start; };
int snake:: get_snake_end() { return snake_end; };


/*LADDER FUNCTION DEFINITIONS*/
int ladder::get_ladder_start() { return ladder_start; };
int ladder::get_ladder_end() { return ladder_end; };


/*BOARD FUNCTION DEFINITIONS*/
int board::get_size() { return size; }
string board::get_type(int i) {
	if (i <= size) {
		return tiles[i - 1].get_type();
	}
	else { return "out of scope"; }
}
void board::occupance(int i, string s) {
	if (i < size) {
		tiles[i].set_occupance(s);
		return;
	}
	else { return; }
}
void board::display() {
	int column_counter = 1;
	int row_counter = 0;
	for (row_counter; row_counter <= rows; row_counter++) { //top row only
		for (column_counter; column_counter <= columns; column_counter++) {
			int i = row_counter * column_counter;
			if (row_counter == 0) {
				cout << " _____ ";
			}
			else if ((rows - row_counter) % 2 == 0) { //rows increasing to right
				int tile_number = size - (columns * row_counter) + column_counter;
				cout << "| ";
				if (tile_number < 10 && get_type(tile_number) != "snake" && get_type(tile_number) != "ladder") { cout << " "; };
				if (get_type(tile_number) == "snake") {
					cout << " * " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else if (get_type(tile_number) == "ladder") {
					cout << " = " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else {
					cout << tiles[tile_number - 1].get_number() << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
			}
			else { //rows increasing to left
				int tile_number = size - (columns * row_counter) + (columns + 1 - column_counter);
				cout << "| ";
				if (tile_number < 10 && get_type(tile_number)!= "snake" && get_type(tile_number) != "ladder") { cout << " "; };
				if (get_type(tile_number) == "snake") {
					cout << " * " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else if (get_type(tile_number) == "ladder") {
					cout << " = " << tiles[tile_number - 1].get_occupied() << " ";
				}
				else {
					cout << tiles[tile_number - 1].get_number() << " " << tiles[tile_number - 1].get_occupied() << " ";
				}
			}
		}
		column_counter = 1;
		cout << endl;
	}
}

/*PLAYER FUNCTION DEFINITIONS*/
string player::get_name() { return name; }
string player::get_initial() { return initial; }
void player::set_position(int i) { position = i; };
int player::get_position() { return position; }
bool player::on_board_check(board& b) { return (position < b.get_size()) ? true : false; }
void player::move(board& b) {

	b.occupance(get_position() - 1, " "); //reset occupance of original tile
	int move_number = roll_dice();
	cout << "Dice : " << move_number << endl;
	string tile_type = b.get_type(get_position());
	set_position(move_number + get_position());
	b.occupance(get_position() - 1, initial); //set new occupance
}
void player::snake_move(board& b, snake& s) {
	int start = s.get_snake_start();
	int end = s.get_snake_end();
	b.occupance(get_position() - 1, " "); //reset occupance
	set_position(end); //move to end of snake
	b.occupance(get_position() - 1, initial); //set new occupance

	cout << "Landed on a snake! Go from " << start << " to " << end << endl;
	b.display();
}

void player::ladder_move(board& b, ladder& l) {
	int start = l.get_ladder_start();
	int end = l.get_ladder_end();
	b.occupance(get_position() - 1, " ");
	set_position(end);
	b.occupance(get_position() - 1, initial);

	cout << "Landed on a ladder! Go from " << start << " to " << end << endl;
	b.display();
}

