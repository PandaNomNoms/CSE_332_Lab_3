#include <string>

#ifndef GAMEPIECE_H
#define GAMEPIECE_H

struct game_piece {
	std::string name_h;
	std::string display_h;
	game_piece(std::string, std::string);
};

#endif

