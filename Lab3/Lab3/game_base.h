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
	void initiateLongest(std::vector<game_piece>, int &);
	void checkLongest(game_piece g, int &);
public:
	static gameBase * getGame(int, char**);
	int play();
	virtual void initialize(std::vector<game_piece>&) = 0;
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual void prompt(int&, int&) = 0;
	virtual void turn() = 0;
	
	gameBase(std::vector<game_piece>, int, int);
	gameBase();
};

#endif