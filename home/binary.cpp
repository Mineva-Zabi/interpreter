#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>


std::map<std::string, int> varTable;

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

int PRIORITY [] = {
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
};

std::string OPERTEXT[] = {
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
};
int OP_NUM = sizeof(PRIORITY) / sizeof(int);


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


LEXTYPE Lexem::getLexType(){
    return lxtp;
}

int Number::getValue() const {
    return value;
}

Number:: Number(){
    value = 0;
}

void Number::print() {
    std::cout << value << ' ';
}

void Number::setValue(int v) {
    value = v;
}

/*Oper::Oper(int op) : Lexem(OPER) {
    opertype = (OPERATOR) op;
}
*/
OPERATOR Oper::getType() {
    return opertype;
}

int Oper::getPriority() {
    return PRIORITY[opertype];
}

Oper::Oper(std::string & op) : Lexem(OPER){
    setType(op);
}

int Oper::getValue(Lexem* left, Lexem* right) const {
    switch(opertype) {
        case PLUS:
            return right->getValue() + left->getValue();
        case MINUS:
            return left->getValue() - right->getValue();
        case MULTIPLY:
            return right->getValue() * left->getValue();
        case ASSIGN:
            left -> setValue(right -> getValue());
            return right->getValue();
        case OR:
            return left->getValue() or right->getValue();
        case AND:
            return left->getValue() and right->getValue();
        case BITOR:
            return left->getValue() | right->getValue();
        case BITAND:
            return left->getValue() & right->getValue();
        case EQ:
            return left->getValue() == right->getValue();
        case NEQ:
            return left->getValue() != right->getValue();
        case XOR:
            return left->getValue() ^ right->getValue();
        case LEQ:
            return left->getValue() <= right->getValue();
        case LT:
            return left->getValue() < right->getValue();
        case GEQ:
            return left->getValue() >= right->getValue();
        case GT:
            return left->getValue() > right->getValue();
        case SHL:
            return left->getValue() << right->getValue();
        case SHR:
            return left->getValue() >> right->getValue();
        case DIV:
            return left->getValue() / right->getValue();
        case MOD:
            return left->getValue() % right->getValue();
    }
    return -1;
}

void Oper::print() {
    std::cout << OPERTEXT[opertype] << ' ';
}

void Oper::setType(std::string op) {
    for (int i = 0; i < OP_NUM; i++) {
        if (op == OPERTEXT[i]) {
            opertype = (OPERATOR)(i);
            break;
        }
    }
}

void printVector(std::vector<Lexem *> infix) {
    int size = infix.size();
    for (int i = 0; i < size; i++) {
        infix[i]->print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

int Variable::getValue() const {
    return varTable[name];
}

void Variable::setValue(int value_) {
    varTable[name] = value_;
}

void Variable::print() {
    std::cout << name << '(' << varTable[name] << ')';
}

Lexem *getNumber(std::string codeline, int & pos) {
    if (!isdigit(codeline[pos]))
        return NULL;
    int number = 0;
    for (int size = codeline.size(); pos < size && isdigit(codeline[pos]); pos++)
        number = number * 10 + codeline[pos] - '0';
    pos--;
    return new Number(number);
}

Lexem *getOper(std::string codeline, int & pos) {
    for (int i = 0; i < OP_NUM; i++) {
        std::string subcodeline = codeline.substr(pos, OPERTEXT[i].size());
        if (OPERTEXT[i] == subcodeline) {
            pos += OPERTEXT[i].size() - 1;
            return new Oper(subcodeline);
        }
    }
    return NULL;
}

bool checkWord(char ch) {
    return ((ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
            ch == '_');
}

Lexem *getVar(std::string codeline, int & i) {
    if (((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
        ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
        (codeline[i] == '_')) {
        std::string name = "";
        while ( (i < codeline.size()) and (
                ((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
                ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
                ((codeline[i] >= '1') and (codeline[i] <= '9')) or
                (codeline[i] == '_')
                )){
            name += codeline[i];
            i++;
        }
        i--;  // for correct incrementation
        return new Variable(name);
    if (varTable.find(name) == varTable.end()) {
            varTable[name] = 0;
        }
    }
    return NULL;
}

std::vector<Lexem *> parseLexem(std::string codeline){
    std::vector<Lexem *> infix;
    for (int i = 0; i < codeline.size(); i++) {
        if ((codeline[i] == ' ') || (codeline[i] == '\t') || (codeline[i] == '\n'))
            continue;
        Lexem *lexem = NULL;
        lexem = getOper(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = getNumber(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = getVar(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
    }
    return infix;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix){
    std::vector<Lexem *> poliz;
    std::stack<Lexem *> opstack;

    for (int i = 0, size = infix.size(); i < size; i++) {
        LEXTYPE lextype = infix[i]->getLexType();
        switch(lextype) {
            case NUMBER: {
                poliz.push_back(infix[i]);
                break;
            }
            case VARIABLE: {
                //std::cout << "akdskdd" << std::endl;
                poliz.push_back(infix[i]);
                break;
            }
            case OPER: {
                switch((infix[i])->getType()) {
                    case LBRACKET: {
                        opstack.push(infix[i]);
                        break;
                    }
                    case RBRACKET: {
                        delete infix[i];
                        while ((opstack.top())->getType() != LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        delete opstack.top();
                        opstack.pop();
                        break;
                    }
                    default: {}
                    while ((opstack.size() > 0) && ((opstack.top())->getPriority() >= (infix[i])->getPriority())){
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.push(infix[i]);
                    }
                }
            default: {}
            }
    }
    while(!opstack.empty()) {
        poliz.push_back(opstack.top());
        opstack.pop();
    }
    return poliz;
}

int evaluatePoliz(std::vector<Lexem *> poliz) {
    std::stack<Lexem *> evalstack;
    Lexem *right, *left;
    for (int i = 0, size = poliz.size(); i < size; i++) {
        switch(poliz[i]->getLexType()) {
            case NUMBER:
                evalstack.push(poliz[i]);
                break;
            case VARIABLE:
                evalstack.push(poliz[i]);
                break;
            case OPER:
                right = evalstack.top();
                evalstack.pop();
                left = evalstack.top();
                evalstack.pop();
                evalstack.push(new Number(poliz[i]->getValue(left, right)));
                delete poliz[i];
                delete left;
                delete right;
                break;
            default: {}
        }
    }
    int ev = evalstack.top() -> getValue();
    delete evalstack.top();
    return ev;
}

void printVar() {
    std::cout << "VARIABLES TABLE:" << std::endl;
    for (std::map<std::string, int>::iterator it = varTable.begin(); it != varTable.end(); it++) {
        std::cout << (it->first) << ' ' << (it->second) << ' ' << std::endl;
    }
}
int main() {
    std::string codeline;
    std::vector <Lexem *> infix;
    std::vector <Lexem *> postfix;
    int value;

    while (std::getline(std::cin, codeline)) {
        // " 10+2 " -> [10 ,+ ,2]
        infix = parseLexem(codeline);
        //[10 ,+ ,2] -> [10 , 2 , +]
        postfix = buildPoliz(infix);
        //[10 , 2 , +] -> 12
        value = evaluatePoliz(postfix);
        std::cout << "Value: " << value << std::endl;
        printVar();
        std::cout << std::endl;
  }
  return 0;
}
