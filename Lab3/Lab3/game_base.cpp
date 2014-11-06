#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "game_base.h"
#include "NineAlmonds.h"
#include "magicSquare.h"
using namespace std;

gameBase * gameBase::getGame(int argc, char* argv[]) {
	if (lowerCase(argv[gameName]) == "ninealmonds") {
		vector<game_piece>* vec = new vector<game_piece>;
		gameBase* game = new NineAlmondsGame(*vec); 
		return game; 
	}
	else if (lowerCase(argv[gameName]) == "magicsquare") {
		vector<game_piece>* vec = new vector<game_piece>;
		gameBase* game = new magicSquare(*vec);
		return game;
	}
	else {
		return nullptr;
	}
}

gameBase::gameBase(vector<game_piece> board, int height, int width)
	:board_h(board), height_h(height), width_h(width)
{}

gameBase::gameBase(){}

void gameBase::initiateLongest(vector<game_piece> board, int & longest) {
	for (game_piece g : board) {
		checkLongest(g, longest);
	}
}

void gameBase::checkLongest(game_piece g, int & longest) {
	if (((int)g.display_h.length()) > longest) {
		longest = (int) (g.display_h.length());
	}
}

/*Begin the game*/
int gameBase::play() {
	initialize(board_h);
	print();
	int counter = 0;
	bool s;
	bool d;
	/*Check if the game is done or if there are any valid moves*/
	while (!((s = stalemate()) || (d = done()))) {
		turn();
		counter++;
	}
	/*Win condition*/
	if (d) {
		cout << "Congratulations, you won!" << endl;
		cout << counter << " turns played." << endl;
		return success;
	}
	/*Lose condition*/
	else {
		cout << "No possible moves left.  You lose." << endl;
		return staleMate;
	}
	/*Should be impossible to reach here*/
	return programLogicError;
}

/*Prompt for NineAlmonds*/
void gameBase::prompt(int& a, int& b) {
	string input;
	/*Inital prompt for input*/
	cout << "Enter coordinates (\"x,y\"), end turn (\"end\"), or quit game (\"quit\"):" << endl;
	cin >> input;
	/*Throw up if user has chosen to quit*/
	if (lowerCase(input) == "quit") {
		cout << "Quitters never win." << endl;
		throw (int)userExit;
	}
	/*Throw up if user has chosen to end turn*/
	else if (lowerCase(input) == "end") {
		cout << "Turn ended." << endl;
		throw "end";
	}
	/*Format the input string*/
	replace(input.begin(), input.end(), ',', ' ');
	/*If the string is not valid, reprompt the user until it is*/
	while (!((istringstream)input >> a >> b)) {
		cout << "Not a valid input, Enter coordinates (\"x,y\"), end turn (\"end\"), or quit game (\"quit\"):" << endl;
		cin >> input;
		if (input == "quit") {
			cout << "Quitters never win." << endl;
			throw (int)userExit;
		}
		else if (lowerCase(input) == "end") {
			cout << "Turn ended." << endl;
			throw "end";
		}
		replace(input.begin(), input.end(), ',', ' ');
	}
}