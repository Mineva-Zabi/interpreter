#ifndef CONST
#define CONST
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

enum LEXTYPE {
    NUMBER, OPER,
    VARIABLE
};
enum OPERATOR {
    LBRACKET, RBRACKET,
    EQ, NEQ,
    ASSIGN,
    OR,
    AND,
    BITOR,
    XOR,
    BITAND,
    SHL, SHR,
    LEQ, LT,
    GEQ, GT,
    PLUS, MINUS,
    MULTIPLY, DIV, MOD
};
extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;
extern std::map<std::string, int> varTable;
#endif
