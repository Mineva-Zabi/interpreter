#include <const.h>

int PRIORITY [] = {
    -2, -1,
    -1,
    -1,
    -1, -1,
    -1, -1,
    -1,
    -1, -1,
    6, 6,
    0,
    1,
    2,
    3,
    4,
    5,
    8, 8,
    7, 7,
    9, 9,
    10, 10, 10
    -2, -1
};

std::string OPERTEXT[] = {
    "[", "]",
    "size",
    "print",
    "if", "else",
    "endif", "while",
    "endwhile",
    "goto", ":",
    "(", ")",
    "==", "!=",
    "=",
    "or",
    "and",
    "|",
    "^",
    "&",
    "<<", ">>",
    "<=", "<",
    ">=", ">",
    "+", "-",
    "*", "/", "%"
    "LVALUE", "RVALUE"
};
int OP_NUM = sizeof(PRIORITY) / sizeof(int);
