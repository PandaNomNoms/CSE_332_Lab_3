// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game_base.h"
#include "common.h"
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
	/*Game board*/
	vector<game_piece> board;
	try {
		/*Get shared pointer*/
		shared_ptr<gameBase> ptr(gameBase::getGame(argc, argv));
		if (ptr == nullptr) {
			/*Error if input incorrect*/
			return usage(argv[programName]);
		}
		return (*ptr).play();
	}
	catch(bad_alloc) {
		return badMem;
	}
	catch (int n) {
		return n;
	}
}

