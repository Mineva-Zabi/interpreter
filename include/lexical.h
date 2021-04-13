#ifndef LEXICAL
#define LEXICAL

#include <lexem.h>

Lexem *getNumber(std::string codeline, int & pos);
Lexem *getOper(std::string codeline, int & pos);
Lexem *getVar(std::string codeline, int & i);
std::vector<Lexem *> parseLexem(std::string codeline);

#endif
