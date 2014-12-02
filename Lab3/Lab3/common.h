#include <string>

#ifndef COMMON_H
#define COMMON_H

extern int reversi_height;
extern int reversi_width;
extern int almond_height;
extern int almond_width;
extern int magicsquare_height;
extern int magicsquare_width;
extern int magicsum;
extern std::string name;
extern std::string display;
extern std::string saveNineAlmonds;
extern std::string saveMagicSquare;
extern std::string saveReversi;

enum indices { programName, gameName, inputNumber };
enum indicesForReversi{reversiProgramName, reversiGameName, blackPieceName, whitePieceName, reversiInputNum};
enum result { success, wrongNumberOfArg, invalidFileName, invalidArgument, couldNotRead, couldNotExtract, noWellFormedDefinitions, dimensionsMismatch, userExit, staleMate, programLogicError, badMem, gamePtrNull, gameAlreadyExist, badGameName };
int usage(char *);
int invalidFile(char *);
int invalidArg(char *);

std::string lowerCase(std::string&);
#endif