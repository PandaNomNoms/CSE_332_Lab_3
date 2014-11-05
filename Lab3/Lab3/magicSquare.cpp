#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "magicSquare.h"
using namespace std;



ostream& operator<<(std::ostream& out, const magicSquare& game){
	const gameBase* handler = &game;
	handler->gameBase::print();
	cout << "\n";
	cout << "Available pieces: ";
	bool print;
	string nameString;
	for (int name = 1; name <= 9; name++){
		print = true;
		nameString = to_string(name);
		for (game_piece piece : game.board_h){
			if (piece.name_h.compare(nameString)!=0){
				print = false;
			}
		}
		cout << nameString << " ";
	}
}