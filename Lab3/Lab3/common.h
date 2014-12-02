#include <string>

#ifndef COMMON_H
#define COMMON_H

extern int almond_height;
extern int almond_width;
extern int magicsquare_height;
extern int magicsquare_width;
extern int magicsum;
extern std::string name;
extern std::string display;
extern std::string saveFileName;

enum indices { programName, gameName, inputNumber };
enum result { success, wrongNumberOfArg, invalidFileName, invalidArgument, couldNotRead, couldNotExtract, noWellFormedDefinitions, dimensionsMismatch, userExit, staleMate, programLogicError, badMem };
int usage(char *);
int invalidFile(char *);
int invalidArg(char *);

std::string lowerCase(std::string);
#endif