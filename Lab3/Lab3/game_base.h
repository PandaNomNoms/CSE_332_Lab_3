#include "stdafx.h"
#include <vector>
#include "game_piece.h"

#ifndef GAMEBASE_H
#define GAMEBASE_H

class gameBase {
protected:
	int width_h;
	int height_h;
	int longest;
	std::vector<game_piece> board_h;
	void initiateLongest(vector<game_piece>, int &);
	void checkLongest(game_piece g, int &);
public:
	gameBase(std::vector<game_piece>, int, int);
	gameBase();
	int getHeight();
	int getWidth();
	std::vector<game_piece> getBoard();
};

#endif