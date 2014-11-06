Timothy Young, Yifu Ma Lab3
Errors:
	indexing mode of gameboard missused
	gameboard not printed after each turn
	stalemate method not checking available pieces

Test Cases:
	When all the pieces are used and the game is not done, a stalemate statment is given
	When a random number is put in for piece, the program says the input is not valid
	When the user tries to use a pieces that is already used, the program says piece already used
	When the coordinate is not valid, the program says input not valid
	When the user try to put another pice to an already occupied slot, the program says the coordinate is not available
	When put in test string 2 0,2 9 0,1 4 0,0 7 1,2 5 1,1 3 1,0 6 2,2 1 2,1 8 2,0, the program successfully returns win