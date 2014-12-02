#include "stdafx.h"
#include "game_base.h"
#include <vector>
#include "game_piece.h"
#include <set>

#ifndef REVERSI_
#define REVERSI_

class reversi : public gameBase{
private:
	std::string blackName;
	std::string whiteName;
	bool blackTurn;
public:
	friend std::ostream& operator<<(std::ostream&, const reversi&);
	reversi(std::vector<game_piece> pieces, std::string blackName, std::string whiteName);
	bool whiteValidMove();
	bool blackValidMove();
	bool checkBlackValid(int&, int&);
	bool checkWhiteValid(int&, int&);
	void print();
	virtual void initialize(std::vector<game_piece>&);
	virtual bool done();
	virtual bool stalemate();
	virtual void turn();
	virtual void save();
	virtual void load(std::vector<game_piece>&);
};

#endif