#ifndef SYNTAX
#define SYNTAX
#include <lexem.h>

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix);
void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> &vec);

#endif
