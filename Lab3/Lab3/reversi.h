#include "stdafx.h"
#include "game_base.h"
#include <vector>
#include "game_piece.h"
#include <set>

#ifndef REVERSI_
#define REVERSI_

class reversi : public gameBase{
private:
	std::set<unsigned int> availablePieces;
public:
	friend std::ostream& operator<<(std::ostream&, const reversi&);
	reversi(std::vector<game_piece> pieces);
	void print();
	virtual void initialize(std::vector<game_piece>&);
	virtual bool done();
	virtual bool stalemate();
	virtual void prompt(unsigned int&);
	virtual void turn();
	void save();
};

#endif