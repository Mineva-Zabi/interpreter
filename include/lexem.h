#ifndef LEXEM
#define LEXEM
#include <const.h>
#include <bits/stdc++.h>
extern std::map<std::string, int> varTable;
extern std::map<std::string, int> labelsMap;
class Lexem {
    LEXTYPE lxtp;
public:
    Lexem();
    Lexem (LEXTYPE type);
    LEXTYPE getLexType();
    virtual void print();
    virtual OPERATOR getType();
    virtual int getPriority();
    virtual int getValue() const;
    virtual void setType(std::string);
    virtual int getValue(Lexem *, Lexem *) const;
    virtual void setValue(int);
    virtual ~Lexem();

};

class Number: public Lexem {
    int value;
public:
    Number();
    Number(int number);
    int getValue() const;
    void print();
    void setValue(int);
    ~Number();
};

class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper();
    Oper(std::string &);
    Oper(OPERATOR op);
    OPERATOR getType();
    int getPriority();
    int getValue(Lexem *, Lexem *) const;
    void setType(std::string);
    void print();
    virtual ~Oper();
};

class Variable: public Lexem {
    std::string name;
public:
    Variable();
    Variable(std::string str);
    int getValue() const;
    void setValue(int);
    std::string getName();
    void print();
    ~Variable();
    bool inLabelsMap();

};

class Goto : public Oper {
    int row;
    OPERATOR oper;
public:
    Goto();
    Goto(OPERATOR opertype);
    void setRow(int);
    void setRow(const std::string name);
    OPERATOR getType();
    int getRow();
    void print();
};

void printVar();
void printLabel();
void printVector(std::vector<Lexem *> infix);
void printVecVec(const std::vector<std::vector<Lexem *>> &infix);

#endif
