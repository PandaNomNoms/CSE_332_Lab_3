/*Commonly used functions and values*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "common.h"
using namespace std;

int almond_height = 5;
int almond_width = 5;
int magicsquare_height = 3;
int magicsquare_width = 3;
int magicsum = 15;
string saveFileName = "default";
string name = "brown almond";
string display = "A";

/*Tells user how to properly use the program*/
int usage(char * c) {
	cout << "Usage: $" << c << " NineAlmonds " << endl << "or" << endl << "$" << c << " MagicSquare" << endl;
	return wrongNumberOfArg;
}

/*Tells user if argument is invalid*/
int invalidArg(char * c) {
	cout << "Error: " << c << " is not a valid argument.  Use \"NineAlmonds\" or \"MagicSquare\"" << endl;
	return invalidArgument;
}

/*Tells user if file is invalid*/
int invalidFile(char * c) {
	cout << "Error: " << c << " is not a valid filename." << endl;
	return invalidFileName;
}

/*Change all strings to all lowercase*/
string lowerCase(string s) {
	for (char c : s) {
		if (c <= 'Z' && c >= 'A') {
			c = c - ('Z' - 'z');
		}
	}
	return s;
}