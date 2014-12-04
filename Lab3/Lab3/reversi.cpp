#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "common.h"
#include "reversi.h"
using namespace std;
//game constructor, takes in the 2 strings passed by main and set them to be the names of 2 players
reversi::reversi(std::vector<game_piece> pieces, std::string blackName, std::string whiteName) : gameBase(pieces, reversi_height, reversi_width) {
	(*this).blackName = blackName;
	(*this).whiteName = whiteName;
}
//the insertion operator definition. Same implementation as MagicSquare and NineAlmonds
ostream& operator<< (ostream& o, const reversi& game) {
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
	o << endl;
	if (game.blackTurn){
		o << game.blackName << "'s turn to play" << endl;
	}
	else{
		o << game.whiteName << "'s turn to play" << endl;
	}
	return o;
}
//print function
void reversi::print(){
	cout << *this;
}
//check if a savefile exists and if so load the savefile and restore the game
void reversi::load(vector<game_piece>& board) {
	ifstream loadFile(saveReversi);
	string line;
	getline(loadFile, line);
	//if the savefile is not empty
	if (loadFile.good() && line != "ITS LITERALLY NOTHING" && line == "valid") {
		cout << "Resuming Reversi" << endl;
		//parse the file and restore the game state
		for (int i = 0; i < height_h*width_h; ++i) {
			getline(loadFile, line);
			string name = line;
			getline(loadFile, line);
			string display = line;
			if (!(name == "" && display == " ")) {
				if (!(name == "black" && display == "X") && !(name == "white" && display == "O")) {
					loadFile.close();
					throw invalidSaveFile;
				}
			}
			board.push_back(game_piece(name, display));
		}
		getline(loadFile, line);
		counter = stoi(line);
		getline(loadFile, line);
		if (line != blackName) {
			cout << "Different player. Starting new game." << endl;
			loadFile.close();
			initialize(board);
			return;
		}
		blackName = line;
		getline(loadFile, line);
		if (line != whiteName) {
			cout << "Different player. Starting new game." << endl;
			loadFile.close();
			initialize(board);
			return;
		}
		whiteName = line;
		getline(loadFile, line);
		//check whose turn is it to play
		if (line == "black") {
			blackTurn = true;
		}
		else if (line == "white") {
			blackTurn = false;
		}
		else {
			cout << "Invalid save file. Starting new game." << endl;
			initialize(board);
			return;
		}
		loadFile.close();
		initiateLongest(board, longest);
	}
	else {
		initialize(board);
	}
}
//initialize the reversi game
void reversi::initialize(std::vector<game_piece>& board){
	board.clear();
	//black piece gets to play first
	blackTurn = true;
	for (int i = 0; i < reversi_height*reversi_width; i++){
		//for the center 4 squares fill them with pieces
		if (i == 27 || i == 36) {
			board.push_back(game_piece("black", "X"));
		}
		else if (i == 28 || i == 35){
			board.push_back(game_piece("white", "O"));
		}
		else{
			//other slots are empty
			board.push_back(game_piece("", " "));
		}
	}
	initiateLongest(board, longest);
	cout << "The reversi game has been initialized" << endl;
}
//check if the game has a winner
bool reversi::done(){
	int blackCount = 0;
	int whiteCount = 0;
	//go through every single slot of the board and count number of black and white pieces
	for (game_piece piece : board_h){
		if (piece.name_h == "black"){
			blackCount++;
		}
		else if (piece.name_h == "white"){
			whiteCount++;
		}
	}
	//if the whole board is filled and the counts are not equal, we have a winner
	if ((blackCount + whiteCount) == (reversi_height * reversi_width)){
		if (blackCount != whiteCount){
			if (blackCount > whiteCount) {
				cout << blackName << " is the winner!" << endl;
			}
			else {
				cout << whiteName << " is the winner!" << endl;
			}
			return true;
		}
	}
	//if the game is in stalemate and the counts are not equal, we have a winner
	if ((!whiteValidMove()) && (!blackValidMove())){
		if (blackCount != whiteCount){
			if (blackCount > whiteCount) {
				cout << blackName << " is the winner!" << endl;
			}
			else {
				cout << whiteName << " is the winner!" << endl;
			}
			return true;
		}
	}
	//else, the game is not done
	return false;
}

//check if there are still valid moves left on the board
bool reversi::stalemate(){
	int blackCount = 0;
	int whiteCount = 0;
	//go through every single slot of the board and count number of black and white pieces
	for (game_piece piece : board_h){
		if (piece.name_h == "black"){
			blackCount++;
		}
		else if (piece.name_h == "white"){
			whiteCount++;
		}
	}
	//if the whole board is filled, and the counts are equal, stalemate
	if ((blackCount + whiteCount) == (reversi_height * reversi_width)){
		if (blackCount == whiteCount){
			return true;
		}
	}
	//if both sides have no valid move and the counts are equal, stalemate
	if ((!whiteValidMove()) && (!blackValidMove())){
		
		if (blackCount == whiteCount){
			return true;
		}
	}
	return false;
}
//check if white pieces have a valid move
bool reversi :: whiteValidMove(){
	string pieceColor;
	string oppoColor;
	int srcIdx;
	int checkIdx;
	int idxDiff;
	//go through every slot on the board
	for (int height = 0; height < reversi_height; height++){
		for (int width = 0; width < reversi_width; width++){
			srcIdx = width + reversi_width * height;
			pieceColor = board_h[srcIdx].name_h;
			//if the slot has a white piece
			if (pieceColor == "white"){
				//check for its surrounding 8 boxes for black pieces
				for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
					for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
						checkIdx = neighborWidth + reversi_width * neighborHeight;
						//makesure the index is in bounds
						if (neighborWidth >= 0 && neighborHeight >= 0 && neighborHeight < height_h && neighborWidth < width_h){
							oppoColor = board_h[checkIdx].name_h;
							if (oppoColor == "black"){
								//if a black piece found, get the difference of 2 indices
								idxDiff = checkIdx - srcIdx;
								//check if a empty slot exists on the other side 
								while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
									checkIdx += idxDiff;
								}
								//if the index is in bound and the slot is empty, we have a valid move
								if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == ""){
								
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	//else, no valid move
	return false;
}
//check valid move for black piece, implementation comparable with whiteValidMove
bool reversi::blackValidMove(){
	string pieceColor;
	string oppoColor;
	int srcIdx;
	int checkIdx;
	int idxDiff;
	for (int height = 0; height < reversi_height; height++){
		for (int width = 0; width < reversi_width; width++){
			srcIdx = width + reversi_width * height;
			pieceColor = board_h[srcIdx].name_h;
			if (pieceColor == "black"){
				for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
					for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
						checkIdx = neighborWidth + reversi_width * neighborHeight;
						if (neighborWidth >= 0 && neighborHeight >= 0 && neighborHeight < height_h && neighborWidth < width_h){
							oppoColor = board_h[checkIdx].name_h;
							if (oppoColor == "white"){
						
								idxDiff = checkIdx - srcIdx;
								
								while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
									checkIdx += idxDiff;
								}
							
								if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == ""){
								
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
//check if a black piece move is valid and flip the pieces if it is valid
bool reversi::checkBlackValid(int& width, int& height){
	string oppoColor = "white";
	int srcIdx = width + reversi_width * height;
	int checkIdx;
	int idxDiff;
	bool ret = false;
	//go through all surrounding slots of the given coordinates on board 
	for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
		for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
			checkIdx = neighborWidth + reversi_width * neighborHeight;
			//if a index is in bound and its color is white
			if (neighborWidth >= 0 && neighborHeight >= 0 && neighborHeight < height_h && neighborWidth < width_h){
				oppoColor = board_h[checkIdx].name_h;
				if (oppoColor == "white"){
					idxDiff = checkIdx - srcIdx;
					//check to see if there is a black piece on the other end of the sequence
					while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
						checkIdx += idxDiff;
					}
					if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == "black"){
						//if a black piece is found, flip all pieces in the sequence
						while (checkIdx != srcIdx){
							checkIdx -= idxDiff;
							board_h[checkIdx].name_h = "black";
							board_h[checkIdx].display_h = "X";

						}
						//set the return variable to be true
						ret = true;
					}
				}
			}
		}
	}
	return ret;
}
//check if a move is valid and flip pieces for white piece, comparable with checkBlackValid
bool reversi::checkWhiteValid(int& width, int& height){
	string oppoColor = "black";
	int srcIdx = width + reversi_width * height;
	int checkIdx;
	int idxDiff;
	bool ret = false;
	for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
		for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
			checkIdx = neighborWidth + reversi_width * neighborHeight;
			if (neighborWidth >= 0 && neighborHeight >= 0 && neighborHeight < height_h && neighborWidth < width_h){
				oppoColor = board_h[checkIdx].name_h;
				if (oppoColor == "black"){
					idxDiff = checkIdx - srcIdx;
					while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
						checkIdx += idxDiff;
					}
					if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == "white"){
						while (checkIdx != srcIdx){
							checkIdx -= idxDiff;
							board_h[checkIdx].name_h = "white";
							board_h[checkIdx].display_h = "O";

						}
						ret = true;
					}
				}
			}
		}
	}
	return ret;
}
//game turn method for reversi game
void reversi::turn(){
	try {
		int width;
		int height;
		//check who's turn it is to play and if the player has a valid move
		if (blackTurn && blackValidMove()){
			cout << blackName << "(X) type in your coordinates" << endl;
		}
		else if ((!blackTurn) && whiteValidMove()){
			cout << whiteName << "(O) type in your coordinates" << endl;
		}
		else{
			//if not, tell them there is no valid move
			cout << "You do not have a valid move" << endl;
			return;
		}
		//prompt the player for input coordinates
		gameBase::prompt(width, height);
		//check if the coordinates are in bound
		while (width < 0 || height < 0 || height >= reversi_height || width >= reversi_width){
			cout << "The coordinates are out of bounds." << endl;
			gameBase::prompt(width, height);
		}
		int pieceIdx = height*reversi_width + width;
		//check if the given coordinates is an empty slot and the move is valid
		if (blackTurn){
			//if not valid, re-prompt for new input
			while (board_h[pieceIdx].name_h != "" || !checkBlackValid(width, height)) {
				cout << "Your move is not valid" << endl;
				gameBase::prompt(width, height);
			}
		}
		else{
			while (board_h[pieceIdx].name_h != "" || !checkWhiteValid(width, height)) {
				cout << "Your move is not valid" << endl;
				gameBase::prompt(width, height);
			}
		}
	}
	catch (char const*) {}
	//give the turn to the other player and print gameboard
	blackTurn = !blackTurn;
	reversi::print();
	
}
//save method for reversi
void reversi::save() {
	string input;
	cout << "Would you like to save the game? (yes/no)" << endl;
	cin >> input;
	//ask if the player wants to save game
	while (lowerCase(input) != "no" && lowerCase(input) != "yes") {
		cout << "Not a valid input. Would you like to save the game? (yes/no)" << endl;
		cin >> input;
	}
	//open a savefile in the same directory to save game
	std::ofstream saveFile;
	saveFile.open(saveReversi, std::ofstream::out | std::ofstream::trunc);
	if (lowerCase(input) == "no") {
		saveFile << "ITS LITERALLY NOTHING" << endl;
		cout << "Quitters never win." << endl;
	}
	else {
		saveFile << "valid" << endl;
		//copy the whole gameboard into savefile
		for (game_piece g : board_h) {
			saveFile << g.name_h << endl << g.display_h << endl;
		}
		counter++;
		saveFile << counter << endl;
		saveFile << blackName << endl;
		saveFile << whiteName << endl;
		//check who's turn it is and save 
		if (blackTurn) {
			saveFile << "black" << endl;
		}
		else {
			saveFile << "white" << endl;
		}
	}
	//close the savefile when done
	saveFile.close();
}