#ifndef LEXICAL
#define LEXICAL

#include <lexem.h>

Lexem *getNumber(std::string codeline, int & pos);
Lexem *getOper(std::string codeline, int & pos);
Lexem *getVar(std::string codeline, int & i);
std::vector<Lexem *> parseLexem(std::string codeline);
void initLabels(std::vector <Lexem*> &infix, int row);
void initJumps(std::vector< std::vector<Lexem *>> infix);

#endif
