// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game_base.h"
#include "common.h"
#include <memory>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	/*Game board*/
	vector<game_piece> board;
	try {
		/*Get shared pointer*/
		gameBase::getGame(argc, argv);
		string saveFileName(argv[gameName]);
		shared_ptr<gameBase> ptr;
		ptr = gameBase::instance();
		return (*ptr).play();
	}
	/*Catch bad memory allocation*/
	catch(bad_alloc) {
		cout << "Bad allocation" << endl;
		return badMem;
	}
	/*Catch any input errors affecting creation of the game*/
	catch (int n) {
		if (n == badGameName || n == wrongNumberOfArg || n == invalidArgument){
			usage(argv[programName]);
		}
		else if (n == gameAlreadyExist) {
			cout << "Another instance of the game is already running" << endl;
		}
		return n;
	}
}

