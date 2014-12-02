// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game_base.h"
#include "common.h"
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != inputNumber) {
		return usage(argv[programName]);
	}
	string saveFileName(argv[gameName]);
	/*Game board*/
	vector<game_piece> board;
	try {
		/*Get shared pointer*/
		gameBase::getGame(argc, argv);
		shared_ptr<gameBase> ptr;
		ptr = gameBase::instance();
		return (*ptr).play();
	}
	catch(bad_alloc) {
		return badMem;
	}
	catch (int n) {
		if (n == badGameName){
			usage(argv[programName]);
		}
		return n;
	}
}

