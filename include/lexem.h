#ifndef LEXEM
#define LEXEM
#include <const.h>

class Lexem {
    LEXTYPE lxtp;
public:
    Lexem(){};
    Lexem (LEXTYPE type) {lxtp = type;}
    LEXTYPE getLexType();
    virtual void print(){}
    virtual OPERATOR getType(){}
    virtual int getPriority(){};
    virtual int getValue() const {};
    virtual void setType(std::string){};
    virtual int getValue(Lexem *, Lexem *) const{};
    virtual void setValue(int){};
    virtual ~Lexem() {};

};

class Number: public Lexem {
    int value;
public:
    Number();
    Number(int number): Lexem(NUMBER), value(number) {}
    int getValue() const;
    void print();
    void setValue(int);
    ~Number(){}
};

class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper() {}
    Oper(std::string &);
    OPERATOR getType();
    int getPriority();
    int getValue(Lexem *, Lexem *) const;
    void setType(std::string);
    void print();
    ~Oper() {}
};

class Variable: public Lexem {
    std::string name;
public:
    Variable() {}
    Variable(std::string str): Lexem(VARIABLE), name(str) {}
    int getValue() const;
    void setValue(int);
    void print();
    ~Variable(){}
};

void printVar();
void printVector(std::vector<Lexem *> infix);


#endif
