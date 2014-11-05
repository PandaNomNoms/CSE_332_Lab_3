#include "stdafx.h"
#include "game_base.h"
#include <vector>
#include "game_piece.h"

#ifndef MAGIC_SQUARE_
#define MAGIC_SQUARE_
class magicSquare : public gameBase{

public:
	friend std::ostream& operator<<(std::ostream&, const magicSquare&);
	magicSquare(std::vector<game_piece> pieces) :gameBase(pieces, 3, 3){
		
	};
};

#endif
