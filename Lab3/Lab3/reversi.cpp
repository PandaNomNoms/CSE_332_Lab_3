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

reversi::reversi(std::vector<game_piece> pieces, std::string blackName, std::string whiteName) : gameBase(pieces, reversi_height, reversi_width) {
	(*this).blackName = blackName;
	(*this).whiteName = whiteName;
}

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
		o << "this is " << game.blackName << "'s turn to play" << endl;
	}
	else{
		o << "this is " << game.whiteName << "'s turn to play" << endl;
	}
	return o;
}

void reversi::print(){
	cout << *this;
}

void reversi::initialize(std::vector<game_piece>& board){
	blackTurn = true;
	for (int i = 0; i < reversi_height*reversi_width; i++){
		if (i == 27 | i == 36){
			board.push_back(game_piece("black", "X"));
		}
		else if (i == 28 | i == 35){
			board.push_back(game_piece("white", "O"));
		}
		else{
			board.push_back(game_piece("", " "));
		}
	}
	initiateLongest(board, longest);
	cout << "the reversi game has been initialized" << endl;
}

bool reversi::done(){
	int blackCount = 0;
	int whiteCount = 0;
	for (game_piece piece : board_h){
		if (piece.name_h == "black"){
			blackCount++;
		}
		else if (piece.name_h == "white"){
			whiteCount++;
		}
	}
	if ((blackCount + whiteCount) == (reversi_height * reversi_width)){
		if (blackCount != whiteCount){
			return true;
		}
	}
	if ((!whiteValidMove()) && (!blackValidMove())){
		if (blackCount != whiteCount){
			return true;
		}
	}
	return false;
}

bool reversi::stalemate(){
	int blackCount = 0;
	int whiteCount = 0;
	for (game_piece piece : board_h){
		if (piece.name_h == "black"){
			blackCount++;
		}
		else if (piece.name_h == "white"){
			whiteCount++;
		}
	}
	if ((blackCount + whiteCount) == (reversi_height * reversi_width)){
		if (blackCount == whiteCount){
			return true;
		}
	}
	if ((!whiteValidMove()) && (!blackValidMove())){
		if (blackCount == whiteCount){
			return true;
		}
	}
	return false;
}

bool reversi :: whiteValidMove(){
	string pieceColor;
	string oppoColor;
	int srcIdx;
	int checkIdx;
	int idxDiff;
	for (int height = 0; height < reversi_height; height++){
		for (int width = 0; width < reversi_width; width++){
			srcIdx = width + reversi_width * height;
			pieceColor = board_h[srcIdx].name_h;
			if (pieceColor == "white"){
				for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
					for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
						checkIdx = neighborWidth + reversi_width * neighborHeight;
						if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width){
							oppoColor = board_h[checkIdx].name_h;
							if (pieceColor != ""&&oppoColor != ""&&pieceColor != oppoColor){
								idxDiff = srcIdx - checkIdx;
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
						if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width){
							oppoColor = board_h[checkIdx].name_h;
							if (pieceColor != ""&&oppoColor != ""&&pieceColor != oppoColor){
								idxDiff = srcIdx - checkIdx;
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

bool reversi::checkBlackValid(int& width, int& height){
	string oppoColor = "white";
	int srcIdx = width + reversi_width * height;
	int checkIdx;
	int idxDiff;
	for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
		for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
			checkIdx = neighborWidth + reversi_width * neighborHeight;
			if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width){
				oppoColor = board_h[checkIdx].name_h;
				if (oppoColor == "white"){
					idxDiff = srcIdx - checkIdx;
					while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
						checkIdx += idxDiff;
					}
					if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == "black"){
						while (checkIdx != srcIdx){
							checkIdx -= idxDiff;
							board_h[checkIdx].name_h = "black";
							board_h[checkIdx].display_h = "X";

						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool reversi::checkWhiteValid(int& width, int& height){
	string oppoColor = "black";
	int srcIdx = width + reversi_width * height;
	int checkIdx;
	int idxDiff;
	for (int neighborHeight = height - 1; neighborHeight <= height + 1; neighborHeight++){
		for (int neighborWidth = width - 1; neighborWidth <= width + 1; neighborWidth++){
			checkIdx = neighborWidth + reversi_width * neighborHeight;
			if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width){
				oppoColor = board_h[checkIdx].name_h;
				if (oppoColor == "black"){
					idxDiff = srcIdx - checkIdx;
					while (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == oppoColor){
						checkIdx += idxDiff;
					}
					if (checkIdx >= 0 && checkIdx < reversi_height * reversi_width && board_h[checkIdx].name_h == "white"){
						while (checkIdx != srcIdx){
							checkIdx -= idxDiff;
							board_h[checkIdx].name_h = "white";
							board_h[checkIdx].display_h = "O";

						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

void reversi::turn(){
	int width;
	int height;
	if (blackTurn && blackValidMove()){
		cout << "black piece type in your coordinates" <<endl ;
	}
	else if ((!blackTurn) && whiteValidMove()){
		cout << "black piece type in your coordinates" << endl;
	}
	else{
		cout <<"you do not have a valid move" << endl;
		return;
	}
	gameBase::prompt(width, height);
	int pieceIdx = height*reversi_width + width;
	while (pieceIdx < 0 || pieceIdx >= reversi_height*reversi_width){
		cout <<"the coordinates are out of bounds"<< endl;
		gameBase::prompt(width, height);
	}
	if (blackTurn){
		while (board_h[pieceIdx].name_h != "" || !checkBlackValid(width, height)){
			cout <<"your move is not valid" << endl;
			gameBase::prompt(width, height);
		}
	}
	else{
		while (board_h[pieceIdx].name_h != "" || !checkWhiteValid(width, height)){
			cout << "your move is not valid" << endl;
			gameBase::prompt(width, height);
		}
	}
	reversi::print();

}