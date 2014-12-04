/*Functions exclusively for the Nine Almonds Game*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "common.h"
#include "NineAlmonds.h"
using namespace std;

NineAlmondsGame::NineAlmondsGame(vector<game_piece>& board) : gameBase(board, almond_height, almond_width) {}

ostream& operator<< (ostream& o, const NineAlmondsGame& game) {
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
	for (int x = 0; x <= game.width_h - 1; x++) {
		o << setw(game.longest) << x << " ";
	}
	o << endl << endl;
	return o;
}

/*Load game if possible*/
void NineAlmondsGame::load(vector<game_piece>& board) {
	ifstream loadFile(saveNineAlmonds);
	string line;
	getline(loadFile, line);
	if (loadFile.good() && line != "ITS LITERALLY NOTHING" && line == "valid") {
		int almonds = 0;
		cout << "Resuming Nine Almonds" << endl;
		/*Load board*/
		for (int i = 0; i < height_h*width_h; ++i) {
			getline(loadFile, line);
			string loadName = line;
			getline(loadFile, line);
			string loadDisplay = line;
			/*If pieces are not valid indicating bad savefile*/
			if (!(loadName == "" && loadDisplay == " ")) {
				if (!(loadName == name) && !(loadDisplay == display)) {
					loadFile.close();
					throw invalidSaveFile;
				}
				almonds++;
			}
			board.push_back(game_piece(name, display));
		}
		/*If more than 9 almonds indicating bad savefile*/
		if (almonds > 9) {
			loadFile.close();
			throw invalidSaveFile;
		}
		/*Get turn counter*/
		getline(loadFile, line);
		counter = stoi(line);
		loadFile.close();
		initiateLongest(board, longest);
	}
	/*If no savefile*/
	else {
		initialize(board);
	}
}

void NineAlmondsGame::initialize(std::vector<game_piece>& board) {
	board.clear();
	/*Create empty board*/
	for (int i = 0; i < height_h * width_h; ++i) {
		board.push_back(game_piece("", " "));
	}
	/*Populate the center 3x3 with almonds*/
	for (int j = 1; j < height_h - 1; j++) {
		for (int i = 1; i < width_h - 1; i++) {
			board[i + width_h*j] = game_piece(name, display);
		}
	}
	initiateLongest(board, longest);
}

bool NineAlmondsGame::done() {
	/*Index of the center square*/
	int mid = (height_h - 1) * width_h / 2 + (width_h - 1) / 2;
	int n = 0;
	/*Check that all squares are empty except for the center square*/
	for (game_piece piece : board_h) {
		if ((n != mid && piece.name_h == name) || (n == mid && piece.name_h != name)) {
			return false;
		}
		n++;
	}
	std::ofstream saveFile;
	saveFile.open(saveNineAlmonds, std::ofstream::out | std::ofstream::trunc);
	saveFile << "ITS LITERALLY NOTHING" << endl;
	return true;
}

bool NineAlmondsGame::stalemate() {
	if (done()) {
		return false;
	}
	int index;
	/*Iterate through each square on the game board*/
	for (int y = 0; y < width_h; y++) {
		for (int x = 0; x < height_h; x++) {
			index = width_h * y + x;
			if (board_h[index].name_h == name) {
				/*Iterate through each piece within one square of the initial piece*/
				for (int dy = -1; dy <= 1; dy++) {
					for (int dx = -1; dx <= 1; dx++) {
						int yadj = y + dy;
						int xadj = x + dx;
						/*Ensure coordinates are within board and is not comparing the original piece*/
						if (xadj >= 0 && xadj < width_h && yadj >= 0 && yadj < height_h && !(dy == 0 && dx == 0)) {
							int adjIndex = width_h * yadj + xadj;
							/*Ensure there is a piece in the space*/
							if (board_h[adjIndex].name_h == name) {
								/*Check that the piece can jump into a valid square*/
								if (xadj + dx > 0 && xadj + dx < width_h && yadj + dy > 0 && yadj + dy < height_h) {
									return false;
								}
							}
						}
					}
				}
			}
		}
	}
	/*Only reaches here if no pieces have valid jumps*/
	std::ofstream saveFile;
	saveFile.open(saveNineAlmonds, std::ofstream::out | std::ofstream::trunc);
	saveFile << "ITS LITERALLY NOTHING" << endl;
	return true;
}

void NineAlmondsGame::turn() {
	int x1, y1, x2, y2;
	/*Prompt user for two sets of coordinates.*/
	try {
		prompt(x1, y1);
		prompt(x2, y2);
	}
	catch (char const*) {
		return;
	}
	/*If the points are not valid, reprompt the user until they are*/
	while (!valid(x1, y1, x2, y2)) {
		cout << "Invalid points, please try again" << endl;
		try {
			prompt(x1, y1);
			prompt(x2, y2);
		}
		catch (char const*) {
			return;
		}
	}
	/*Print out the board and ask the user if they wish to continue the turn*/
	cout << endl << board_h;
	string out = to_string(x1) + "," + to_string(y1) + " to " + to_string(x2) + "," + to_string(y2);
	cout << out << endl;
	if (stalemate() || done()) {
		return;
	}
	string in;
	cout << "Continue this turn (YyNn)?" << endl;
	cin >> in;
	in = lowerCase(in);
	/*If the input is not valid, reprompt the user until it is*/
	while (in != "no" && in != "n" && in != "yes" && in != "y") {
		cout << "Invalid input, please try again." << endl;
		cout << "Continue this turn (YyNn)?" << endl;
		cin >> in;
	}
	/*While the user wishes to continue the turn*/
	while (in == "yes" || in == "y") {
		/*Set the 2nd point to the first point and prompt for a second point*/
		x1 = x2;
		y1 = y2;
		try {
			prompt(x2, y2);
		}
		catch (char const*) {
			return;
		}
		/*If the point is not valid, reprompt until it is*/
		while (!valid(x1, y1, x2, y2)) {
			cout << "Invalid point, please try again" << endl;
			try {
				prompt(x2, y2);
			}
			catch (char const*) {
				return;
			}
		}
		/*Print board and add to the chain of coordinates*/
		cout << endl << board_h;
		string temp = out;
		string out = temp + " to " + to_string(x2) + "," + to_string(y2);
		cout << out << endl;
		if (stalemate() || done()) {
			return;
		}
		cout << "Continue this turn (YyNn)?" << endl;
		cin >> in;
		in = lowerCase(in);
		/*If the input is not valid, reprompt until it is*/
		while (in != "no" && in != "n" && in != "yes" && in != "y") {
			cout << "Invalid input, please try again." << endl;
			cout << "Continue this turn (YyNn)?" << endl;
			cin >> in;
		}
	}
	cout << "Turn ended." << endl;
}

bool NineAlmondsGame::valid(int x1, int y1, int x2, int y2) {
	/*Check if parameters are within the board*/
	if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 || x1 >= width_h || x2 >= width_h || y1 >= height_h || y2 >= height_h) {
		return false;
	}
	int index1 = width_h * y1 + x1;
	int index2 = width_h * y2 + x2;
	int midx = (x1 + x2) / 2;
	int midy = (y1 + y2) / 2;
	int midindex = height_h * midy + midx;
	/*Check if the initial spot has an almond, the middle spot has an almond, and the final spot is empty*/
	if (board_h[index1].name_h != name || board_h[index2].name_h != "" || board_h[midindex].name_h != name) {
		return false;
	}
	int dx = x2 - x1;
	int dy = y2 - y1;
	/*Check that the points are exactly two squares from each other*/
	if (!((dx == 0 || abs(dx) == 2) && (dy == 0 || abs(dy) == 2))) {
		return false;
	}

	/*Perform the move and return*/
	board_h[width_h*y1 + x1] = game_piece("", " ");
	board_h[width_h*midy + midx] = game_piece("", " ");
	board_h[width_h*y2 + x2] = game_piece(name, display);
	return true;
}

void NineAlmondsGame::print() {
	cout << *this;
}

/*Asks user if they wish to save the game*/
void NineAlmondsGame::save() {
	string input;
	cout << "Would you like to save the game? (yes/no)" << endl;
	cin >> input;
	while (lowerCase(input) != "no" && lowerCase(input) != "yes") {
		cout << "Not a valid input. Would you like to save the game? (yes/no)" << endl;
		cin >> input;
	}
	std::ofstream saveFile;
	saveFile.open(saveNineAlmonds, std::ofstream::out | std::ofstream::trunc);
	/*Clears savefile*/
	if (lowerCase(input) == "no") {
		saveFile << "ITS LITERALLY NOTHING" << endl;
		cout << "Quitters never win." << endl;
	}
	/*Saves current state of the game*/
	else {
		saveFile << "valid" << endl;
		for (game_piece g : board_h) {
			saveFile << g.name_h << endl << g.display_h << endl;
		}
		counter++;
		saveFile << counter << endl;
	}
	saveFile.close();
}