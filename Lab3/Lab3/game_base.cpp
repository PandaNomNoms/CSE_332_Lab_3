#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "game_base.h"
using namespace std;

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
	if (g.display_h.length > longest) {
		longest = g.display_h.length;
	}
}

int gameBase::getHeight() {
	return height_h;
}

int gameBase::getWidth() {
	return width_h;
}

int gameBase::getLongest() {
	return longest;
}

vector<game_piece> gameBase::getBoard() {
	return board_h;
}

void gameBase::prompt(int& a, int& b) {
	string input;
	/*Inital prompt for input*/
	cout << "Enter coordinates (\"x,y\") or quit game (\"quit\"):" << endl;
	std::cin >> input;
	/*Throw up if user has chosen to quit*/
	if (input == "quit") {
		throw (int)userExit;
		return;
	}
	/*Format the input string*/
	replace(input.begin(), input.end(), ',', ' ');
	/*If the string is not valid, reprompt the user until it is*/
	while (!((istringstream)input >> a >> b)) {
		cout << "Not a valid input, Enter coordinates (\"x,y\") or quit game (\"quit\"):" << endl;
		std::cin >> input;
		if (input == "quit") {
			throw (int)userExit;
			return;
		}
		replace(input.begin(), input.end(), ',', ' ');
	}
}