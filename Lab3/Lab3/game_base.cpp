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

vector<game_piece> gameBase::getBoard() {
	return board_h;
}

