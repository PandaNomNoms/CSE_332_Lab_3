#include "game_piece.h"
#include "game_base.h"
#include <vector>

#ifndef NINEALMONDS_H
#define NINEALMONDS_H

class NineAlmondsGame : public gameBase {
	friend std::ostream& operator<< (std::ostream&, const NineAlmondsGame&);
	void initialize(std::vector<game_piece>&);
	void load(std::vector<game_piece>&);
public:
	NineAlmondsGame(std::vector<game_piece>&);
	int play();
	bool done();
	bool stalemate();
	void turn();
	bool valid(int, int, int, int);
	void print();
	void save();

};

std::ostream& operator<< (std::ostream &, const NineAlmondsGame &);

#endif NINEALMONDS_H