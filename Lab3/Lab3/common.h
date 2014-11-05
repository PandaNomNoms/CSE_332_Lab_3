#include <string>

#ifndef COMMON_H
#define COMMON_H

extern int height;
extern int width;
extern std::string name;
extern std::string display;

enum indices { programName, gameName, inputNumber };
enum result { success, wrongNumberOfArg, invalidFileName, invalidArgument, couldNotRead, couldNotExtract, noWellFormedDefinitions, dimensionsMismatch, userExit, staleMate, programLogicError };
int usage(char *);
int invalidFile(char *);
int invalidArg(char *);

std::string lowerCase(std::string);
#endif