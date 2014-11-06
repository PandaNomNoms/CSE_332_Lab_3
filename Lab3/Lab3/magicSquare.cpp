/*Functions exclusively for the Magic Square game*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "magicSquare.h"
using namespace std;

/*Print out the magic square*/
void magicSquare::print(){
	cout << *this;
}

magicSquare::magicSquare(std::vector<game_piece> pieces) : gameBase(pieces, magicsquare_height, magicsquare_width) {}

/*Initialize the magic square board*/
void magicSquare::initialize(vector<game_piece>& pieces) {
	for (int i = 0; i < (magicsquare_height * magicsquare_width); i++){
		pieces.push_back(game_piece("empty", " "));
		availablePieces.insert(i);
	}
	initiateLongest(board_h, longest);
	cout << "The game magic square is constructed." << endl;
}

/*Put magic square into ostream*/
ostream& operator<<(std::ostream& o, const magicSquare& game){
	int index;
	cout << endl;
	/*Print row*/
	for (int y = game.height_h - 1; y >= 0; y--) {
		/*Print y-axis*/
		o << y << " ";
		/*Print column*/
		for (int x = 0; x <= game.height_h - 1; x++) {
			index = game.width_h * y + x;
			o << setw(game.longest) << game.board_h[index].display_h << " ";
		}
		o << endl;
	}
	/*Print x-axis*/
	o << "x ";
	for (int x = 0; x <= game.height_h - 1; x++) {
		o << setw(game.longest) << x << " ";
	}
	o << endl;
	o << "Available pieces: ";
	for (int i : game.availablePieces) { 
		cout << i << " ";
	}
	cout << endl << endl;
	return o;
}

/*Check if the magic square has been solved*/
bool magicSquare::done(){
// Test string: 2 0,2 9 0,1 4 0,0 7 1,2 5 1,1 3 1,0 6 2,2 1 2,1 8 2,0
	/*Check that the board is completely filled*/
	for (game_piece piece : board_h) {
		if (piece.name_h == "empty") {
			return false;
		}
	}
	/*Check the rows*/
	for (int height = 0; height < magicsquare_height; height++){
		if (stoi(board_h[height * magicsquare_width].name_h) + stoi(board_h[height * magicsquare_width + 1].name_h) + stoi(board_h[height * magicsquare_width + 2].name_h) != magicsum){
			return false;
		}
	}
	/*Check the columns*/
	for (int width = 0; width < magicsquare_width; width++){
		if (stoi(board_h[width].name_h) + stoi(board_h[magicsquare_height + width].name_h) + stoi(board_h[2 * (magicsquare_height) + width].name_h) != magicsum){
			return false;
		}
	}
	/*Check upwards diagonal*/
	if (stoi(board_h[0].name_h) + stoi(board_h[4].name_h) + stoi(board_h[8].name_h) != magicsum){
		return false;
	}
	/*Check downwards diagonal*/
	if (stoi(board_h[6].name_h) + stoi(board_h[4].name_h) + stoi(board_h[2].name_h) != magicsum){
		return false;
	}
	return true;
}

/*Check that no pieces are left to play*/
bool magicSquare::stalemate(){
	if (availablePieces.size() != 0){
		return false;
	}
	cout << "All pieces used" << endl;
	return !done();
}

/*Prompt user for input*/
void magicSquare::prompt(unsigned int &num){
	string input;
	/*Inital prompt for input*/
	cout << "Enter a piece(\"n\") or quit(\"quit\"):" << endl;
	std::cin >> input;
	/*Throw up if user has chosen to quit*/
	if (lowerCase(input) == "quit") {
		cout << "Quitters never win." << endl;
		throw (int)userExit;
	}
	/*Reprompt if the input is not valid*/
	while (!((istringstream)input >> num) || (int)num > (magicsquare_height*magicsquare_width) || (int)num < 0) {
		cout << "Your input is not valid! Either not a number, not a valid piece, or the piece is not available" << endl;
		std::cin >> input;
		if (lowerCase(input) == "quit") {
			cout << "Quitters never win." << endl;
			throw (int)userExit;
		}
	}
}

/*Give user his turn*/
void magicSquare::turn() {
	try{
		unsigned int piece;
		/*Prompt for piece*/
		magicSquare::prompt(piece);
		/*Ensure piece is not used*/
		while (availablePieces.find(piece) == availablePieces.end()){
			cout << "The piece is used" << endl;
			magicSquare::prompt(piece);
		}
		int x, y;
		/*Prompt for coordinates*/
		gameBase::prompt(x, y);
		/*Ensure coordinates are valid*/
		while ((board_h[y * magicsquare_width + x].name_h != "empty") || (x >= magicsquare_width) || (y >= magicsquare_height) || (x < 0) || (y < 0)) {
			cout << "The coordinate is not available." << endl;
			gameBase::prompt(x, y);
		}
		/*Change the game_piece to the placed one*/
		cout << "You decided to put piece " << piece << " at coordinate " << x << ", " << y << endl;
		board_h[y * magicsquare_width + x].display_h = to_string(piece);
		board_h[y * magicsquare_width + x].name_h = to_string(piece);
		/*Update longest if necessary*/
		checkLongest(board_h[y * magicsquare_width + x], longest);
		availablePieces.erase(piece);
		magicSquare::print();
		return;
	}
	catch (char const*) {}
}