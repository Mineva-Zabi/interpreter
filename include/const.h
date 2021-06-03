#ifndef CONST
#define CONST
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

enum LEXTYPE {
    NUMBER, OPER,
    VARIABLE, ARRAY
};
enum OPERATOR {
    LSQUBR, RSQUBR,
	SIZE,
    PRINT,
    IF, ELSE,
    ENDIF, WHILE,
    ENDWHILE,
    GOTO, COLON,
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
    MULTIPLY, DIV, MOD,
    LVALUE, RVALUE
};
extern int PRIORITY[];
extern std::string OPERTEXT[];
extern int OP_NUM;

#endif
