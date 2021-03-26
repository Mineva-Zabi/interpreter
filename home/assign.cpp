#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>


std::map<std::string, int> _map;

enum LEXTYPE {
    NUMBER, OPER,
    VARIABLE
};

enum OPERATOR {
    LBRACKET, RBRACKET,
    ASSIGN,
    PLUS, MINUS,
    MULTIPLY
};

int PRIORITY [] = {
    -1 , -1 ,
    0,
    1, 1,
    2
};

std::string OPERTEXT[] = {
    "(", ")",
    "=",
    "+", "-",
    "*"
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
    virtual int getValue(){};
    virtual void setType(std::string){};
    virtual int getValue(Lexem *, Lexem *){};
    virtual void setValue(int value){};
    virtual ~Lexem() {};

};

class Number: public Lexem {
    int value;
public:
    Number();
    Number(int number): Lexem(NUMBER), value(number) {}
    int getValue() const;
    void print();
    ~Number(){}
};

class Oper: public Lexem {
    OPERATOR opertype;
public:
    Oper(){}
    Oper(std::string &);
    OPERATOR getType();
    int getPriority();
    int getValue(Lexem *, Lexem *);
    void setType(std::string);
    void print();
    ~Oper(){}
};

class Variable: public Lexem {
    std::string name;
public:
    Variable(){}
    Variable(std::string str): Lexem(VARIABLE), name(str) {}
    int getValue();
    void setValue(int value);
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

int Oper::getValue(Lexem* left, Lexem* right) {
    int res;
    switch (opertype) {
        case PLUS: {
            res = left->getValue() + right->getValue();
            break;
        }
        case MINUS: {
            res = left->getValue() - right->getValue();
            break;
        }
        case MULTIPLY: {
            res = left->getValue() * right->getValue();
            break;
        }
        case ASSIGN: {
            left->setValue(right -> getValue());
            res = right->getValue();
            break;
        }
        default: {}
    }
    return res;
}

void Oper::print() {
    std::cout << OPERTEXT[opertype] << ' ';
}

void Oper :: setType(std::string op) {
    for (int i = 0; i < OP_NUM; i++) {
        if (op == OPERTEXT[i]) {
            opertype = static_cast<OPERATOR>(i);
            break;
        }
    }
}

void print_vector(std::vector<Lexem *> infix) {
    int size = infix.size();
    for (int i = 0; i < size; i++) {
        infix[i]->print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

int Variable::getValue() {
    return _map[name];
}

void Variable::setValue(int value_) {
    _map[name] = value_;
}

void Variable::print() {
    std::cout << name << '(' << _map[name] << ')';
}

Lexem *get_number(std::string codeline, int & pos) {
    if (!isdigit(codeline[pos]))
        return NULL;
    int number = 0;
    for (int size = codeline.size(); pos < size && isdigit(codeline[pos]); pos++)
        number = number * 10 + codeline[pos] - '0';
    pos--;
    return new Number(number);
}

Lexem *get_oper(std::string codeline, int & pos) {
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

Lexem *get_var(std::string codeline, int & pos) {
    int size = codeline.size();
    std::string var = "";
    for (int i = pos; i < size; i++) {
        if (checkWord(codeline[pos])) {
            var += codeline[i];
        }
    }
    pos--;
    if(_map.find(var) == _map.end()){
        _map[var] = 0;
    }
    return new Variable(var);
}

std::vector<Lexem *> parseLexem(std::string codeline){
    std::vector<Lexem *> infix;
    for (int i = 0; i < codeline.size(); i++) {
        if ((codeline[i] == ' ') || (codeline[i] == '\t') || (codeline[i] == '\n'))
            continue;
        Lexem *lexem = NULL;
        lexem = get_oper(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = get_number(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = get_var(codeline, i);
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
                    default:
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
                evalstack.push(new Number(poliz[i] -> getValue(left, right)));
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
    for (std::map<std::string, int>::iterator it = _map.begin(); it != _map.end(); it++) {
        std::cout << it->first << ' ' << it->second << ' ' << std::endl;
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
