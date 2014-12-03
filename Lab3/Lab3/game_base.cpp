/*Shared game functions*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "common.h"
#include "game_base.h"
#include "NineAlmonds.h"
#include "magicSquare.h"
#include "reversi.h"
using namespace std;

	
shared_ptr<gameBase> gameBase::gamePtr = nullptr;

shared_ptr<gameBase> gameBase::instance(){
	if (gameBase::gamePtr != nullptr){
		return gameBase::gamePtr;
	}
	else{
		throw (int)gamePtrNull;
	}
}

/*Determines whether to construct a Nine Almonds Game or Magic Square Game*/
void gameBase::getGame(int argc, char* argv[]) {
	/*Nine Almonds Game Case*/
	if (lowerCase(string(argv[gameName])) == "ninealmonds") {
		if (gamePtr != nullptr){
			throw (int)gameAlreadyExist;
		}
		else{
		vector<game_piece>* vec = new vector<game_piece>;
			gamePtr = shared_ptr<gameBase>(new NineAlmondsGame(*vec));
		}
		
	}
	/*Magic Square Game Case*/
	else if (lowerCase(string(argv[gameName])) == "magicsquare") {
		if (gamePtr != nullptr){
			throw (int)gameAlreadyExist;
		}
		else{
			vector<game_piece>* vec = new vector<game_piece>;
			gamePtr = shared_ptr<gameBase>(new magicSquare(*vec));
		}
	}
	/*Neither Case*/
	else if(lowerCase(string(argv[reversiGameName])) == "reversi"){
	
		if (argc != reversiInputNum){
			
			throw (int)wrongNumberOfArg;
		}
		if (gamePtr != nullptr){
			
			throw (int)gameAlreadyExist;
		}
		else{
			vector<game_piece>* vec = new vector<game_piece>;
			gamePtr = shared_ptr<gameBase>(new reversi(*vec, argv[blackPieceName], argv[whitePieceName]));
			
		}
	}
}

/*Constructor for gameBase*/
gameBase::gameBase(vector<game_piece> board, int height, int width)
	:board_h(board), height_h(height), width_h(width)
{}

/*Default constructor for gameBase*/
gameBase::gameBase(){}

/*Give longest an initial value*/
void gameBase::initiateLongest(vector<game_piece> board, int & longest) {
	for (game_piece g : board) {
		checkLongest(g, longest);
	}
}

/*Update longest value*/
void gameBase::checkLongest(game_piece g, int & longest) {
	if (((int)g.display_h.length()) > longest) {
		longest = (int) (g.display_h.length());
	}
}

/*Begin the game*/
int gameBase::play() {
	load(board_h);
	print();
	int counter = 0;
	bool s = stalemate();
	bool d = done();
	/*Check if the game is done or if there are any valid moves*/
	while (!s && !d) {
		turn();
		counter++;
		s = stalemate();
		d = done();
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

/*Prompt*/
void gameBase::prompt(int& a, int& b) {
	string input;
	/*Inital prompt for input*/
	cout << "Enter coordinates (\"x,y\"), end turn (\"end\"), or quit game (\"quit\"):" << endl;
	cin >> input;
	/*Throw up if user has chosen to quit*/
	if (lowerCase(input) == "quit") {
		save();
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
		if (lowerCase(input) == "quit") {
			save();
			throw (int)userExit;
		}
		else if (lowerCase(input) == "end") {
			cout << "Turn ended." << endl;
			throw "end";
		}
		replace(input.begin(), input.end(), ',', ' ');
	}
}