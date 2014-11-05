#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "common.h"
#include "magic_square.h"
using namespace std;

ostream& operator<<(std::ostream& out, const magic_square& game){
	game.print();
	cout << "\n";
	cout << "Available pieces: ";
}