#include "stdafx.h"
#include "game_base.h"
#include <vector>
#include "game_piece.h"

#ifndef MAGIC_SQUARE_
#define MAGIC_SQUARE_
class magic_square : public gameBase{
	
public:
	friend std::ostream& operator<<(std::ostream&, const magic_square&);
	magic_square(std::vector<game_piece> pieces) :gameBase(pieces, 3, 3){
		
	};
};

#endif