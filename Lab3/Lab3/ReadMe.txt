Timothy Young, Yifu Ma Lab4
Errors:
	lowercase method not working in some cases (fixed)
	returning error when coordinate outside board entered (fixed)


Test Cases:
input: lab4.exe
output:
Usage: $lab4.exe NineAlmonds
or
$lab4.exe MagicSquare
or
$lab4.exe Reversi "Player 1" "Player 2"
errorlevel: 1

input: lab4.exe abc
output:
Usage: $lab4.exe NineAlmonds
or
$lab4.exe MagicSquare
or
$lab4.exe Reversi "Player 1" "Player 2"
errorlevel: 3

input: lab4.exe ninealmonds
output: depending on the success of game, can either be

quitting the game (errorlevel 8)
winning (errorlevel 0)
stalemate (errorlevel 9)

input: lab4.exe magicsquare
output: depending on the success of game, can either be

quitting the game (errorlevel 8)
winning (errorlevel 0)
stalemate (errorlevel 9)

input: lab4.exe reversi Alice
output: 
Usage: $lab4.exe NineAlmonds
or
$lab4.exe MagicSquare
or
$lab4.exe Reversi "Player 1" "Player 2"
errorlevel: 1

input: lab4.exe reversi Alice Bob
output: depending on the success of game, can either be

quitting the game (errorlevel 8)
winning (errorlevel 0)
stalemate (errorlevel 9)

If a non-valid savefile is loaded into the game, the game will create a new game board.
Similarly, if a reversi game is begun with different players than the saved game, a new game will be started.
All turns, number of turns taken, and piece positions on the board are preserved.
All savefiles are saved as "<game_name>.txt"

With regards to copy constructors, move constructors, copy-assignment operators, move-assignment operators, and destructors, these were not implemented in ninealmonds and magicsquare initially so we did not alter them to include these.
For reversi we decided against implementing them as well since the two other games had run fine without these operators and we wished to reuse code that we had implemented previously.
Instead we repeated what we had done previously, creating/replacing pieces within the game board at the beginning of the game and modifying them as the game progressed.
Also, since the game has relatively small memory requirements and after main has exited, the game and everything in it is deleted, we felt that such memory management was unnecessary.