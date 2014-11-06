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
			cout << "piece not all used" << endl;
			return false;
		}
	}
	for (int height = 0; height < magicsquare_height; height++){
		if (stoi(board_h[height * (magicsquare_width) + 1].name_h) + stoi(board_h[height * (magicsquare_width) + 2].name_h) + stoi(board_h[height * (magicsquare_width) + 3].name_h) != 15){
			cout << "not all rows sum up to 15"<< endl;
			return false;
		}
	}
	for (int width = 0; width < magicsquare_width;width++){
		if (stoi(board_h[(magicsquare_height) + width].name_h) + stoi(board_h[2 * (magicsquare_height) + width].name_h) + stoi(board_h[3 * (magicsquare_height) + width].name_h) != 15){
			cout <<"not all columns sum up to 15" << endl;
			return false;
		}
	}
	if (stoi(board_h[0].name_h) + stoi(board_h[8].name_h) + stoi(board_h[4].name_h) != 15){
		cout << "the bottom left top right diagonal line is not 15"<< endl;
		return false;
	}
	if (stoi(board_h[2].name_h) + stoi(board_h[6].name_h) + stoi(board_h[4].name_h) != 15){
		cout << "the bottom right top left diagonal line is not 15" << endl;
		return false;
	}
	return true;
}

bool magicSquare::stalemate(){
	if (availablePieces.size() != 0){
		cout << "still pieces to use"<< endl;
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
	while (!((istringstream)input >> num )){
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
		while (x < 0 || x > (magicsquare_width) || y < 0 || y > (magicsquare_height) || board_h[(y ) * magicsquare_width + x].name_h.length() == 1){
			cout << "Your input is not valid" << endl;
			gameBase::prompt(x, y);
		}
		cout << "You decided to put piece " << piece << " at coordinate " << x << ", " << y << endl;
		board_h[(y ) * magicsquare_width + x].display_h = to_string(piece);
		board_h[(y ) * magicsquare_width + x].name_h = to_string(piece);
		availablePieces.erase(piece);
		print();
		return;
	}
	catch(int x){
		cout << "Quitters never win" << endl;
		throw (int)userExit;
	}

}