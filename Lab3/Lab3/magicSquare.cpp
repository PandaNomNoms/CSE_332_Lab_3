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
	cout<<this;
}
magicSquare::magicSquare(std::vector<game_piece> pieces) : gameBase(pieces, 4, 4){
	
	for (int i = 1; i < 10; i++){
		availablePieces.insert(i);
	}
	std::cout << "the game magic square is constructed" << endl;
};
ostream& operator<<(std::ostream& o, const magicSquare& game){
	int index;
	/*Print row*/
	for (int y = game.getHeight - 1; y >= 0; y--) {
		/*Print y-axis*/
		o << y << " ";
		/*Print column*/
		for (int x = 0; x <= game.getHeight - 1; x++) {
			index = game.getWidth * y + x;
			o << setw(game.getLongest) << game.getBoard[index].display_h << " ";
		}
		o << endl;
	}
	/*Print x-axis*/
	o << "x ";
	for (int x = 0; x <= game.getWidth - 1; x++) {
		o << setw(game.getLongest) << x << " ";
	}
	o << "\n";
	o << "Available pieces: ";
	for (int i : game.availablePieces){
		cout << i << " ";
	}
	return o;
}

bool magicSquare::done(){

	for (game_piece piece : board_h){
		if (piece.name_h.length != 1){
			return false;
		}
	}
	for (int height = 1; height < 4; height++){
		if (stoi(board_h[height * 4 + 1].name_h) + stoi(board_h[height * 4 + 2].name_h) + stoi(board_h[height * 4 + 3].name_h) != 15){
			return false;
		}
	}
	for (int width = 1; width < 4;width++){
		if (stoi(board_h[4 + width].name_h) + stoi(board_h[2 * 4 + width].name_h) + stoi(board_h[3 * 4 + width].name_h) != 15){
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
		if (piece.name_h.length != 1){
			return false;
		}
	}
	return !done();
}

void magicSquare::prompt(unsigned int &num){
	string input;
	/*Inital prompt for input*/
	cout << "Enter a piece or quit game (\"quit\"):" << endl;
	std::cin >> input;
	/*Throw up if user has chosen to quit*/
	if (input == "quit") {
		throw (int)userExit;
		return;
	}
	while (!(istringstream)input >> num || availablePieces.find(num) == availablePieces.end()){
		cout << "your input is not valid! Either not a number or the piece is not available" << endl;
		std::cin >> input;
		if (input == "quit") {
			throw (int)userExit;
			return;
		}
	}
}

void magicSquare::turn(){
	unsigned int piece;
	magicSquare::prompt(piece);
	while (availablePieces.find(piece) == availablePieces.end()){
		cout << "the piece is already used" << endl;
		magicSquare::prompt(piece);
	}
	int x, y;
	gameBase::prompt(x, y);
	while (x<0 || x>2 || y < 0 || board_h[(y+1)*4+x].name_h.length==1){
		cout << "The coordinate you put in is not valid" << endl;
		gameBase::prompt(x, y);
	}
}