#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "magicSquare.h"
using namespace std;

void magicSquare::print(){
	cout << *this;
}

magicSquare::magicSquare(std::vector<game_piece> pieces) : gameBase(pieces, magicsquare_height, magicsquare_width) {}

void magicSquare::initialize(vector<game_piece>& pieces) {
	for (int i = 0; i < ((magicsquare_height + 1) * (magicsquare_width + 1)); i++){
		pieces.push_back(game_piece("empty", " "));
	}
	for (int i = 1; i <= ((magicsquare_height)*(magicsquare_width)); i++){
		availablePieces.insert(i);
	}
	cout << "The game magic square is constructed." << endl;
}

ostream& operator<<(std::ostream& o, const magicSquare& game){
	int index;
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
	for (int i : game.availablePieces){
		cout << i << " ";
	}
	cout << endl;
	return o;
}

bool magicSquare::done(){

	for (game_piece piece : board_h){
		if (piece.name_h.length() != 1){
			return false;
		}
	}
	for (int height = 1; height < 4; height++){
		if (stoi(board_h[height * (magicsquare_width + 1) + 1].name_h) + stoi(board_h[height * (magicsquare_width + 1) + 2].name_h) + stoi(board_h[height * (magicsquare_width + 1) + 3].name_h) != 15){
			return false;
		}
	}
	for (int width = 1; width < 4;width++){
		if (stoi(board_h[(magicsquare_height + 1) + width].name_h) + stoi(board_h[2 * (magicsquare_height + 1) + width].name_h) + stoi(board_h[3 * (magicsquare_height + 1) + width].name_h) != 15){
			return false;
		}
	}
	if (stoi(board_h[5].name_h) + stoi(board_h[15].name_h) + stoi(board_h[10].name_h) != 15){
		return false;
	}
	if (stoi(board_h[12].name_h) + stoi(board_h[7].name_h) + stoi(board_h[10].name_h) != 15){
		return false;
	}
	return true;
}

bool magicSquare::stalemate(){
	for (game_piece piece : board_h){
		if (piece.name_h.length() != 1){
			return false;
		}
	}
	return !done();
}

void magicSquare::prompt(unsigned int &num){
	string input;
	/*Inital prompt for input*/
	cout << "Enter a piece:" << endl;
	std::cin >> input;
	/*Throw up if user has chosen to quit*/
	if (lowerCase(input) == "quit") {
		throw (int)userExit;
	}
	while (!(istringstream)input >> num){
		cout << "Your input is not valid! Either not a number or the piece is not available" << endl;
		std::cin >> input;
		if (lowerCase(input) == "quit") {
			throw (int) userExit;
		}
	}
}

void magicSquare::turn() {
	try{
		unsigned int piece;
		magicSquare::prompt(piece);
		while (availablePieces.find(piece) == availablePieces.end()){
			cout << "The piece is used" << endl;
			magicSquare::prompt(piece);
		}
		int x, y;
		gameBase::prompt(x, y);
		while (x < 0 || x > (magicsquare_width-1) || y < 0 || y > (magicsquare_height-1) || board_h[(y + 1) * magicsquare_width + x + 2].name_h.length() == 1){
			cout << "Your input is not valid" << endl;
			gameBase::prompt(x, y);
		}
		cout << "You decided to put piece " << piece << " at coordinate " << x << ", " << y << endl;
		board_h[(y + 1) * magicsquare_width + x + 1].display_h = " ";
		board_h[(y + 1) * magicsquare_width + x + 1].name_h = "empty";
		availablePieces.erase(piece);
		return;
	}
	catch(int x){
		cout << "Quitters never win" << endl;
		throw (int)userExit;
	}

}