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
//int OP_NUM = sizeof(PRIORITY) / sizeof(int);


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
    Oper(int op);
    OPERATOR getType();
    int getPriority();
    int getValue(Lexem *, Lexem *);
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

std::map<std::string, int> _map;

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

Oper::Oper(int op) : Lexem(OPER) {
    opertype = (OPERATOR) op;
}

OPERATOR Oper::getType() {
    return opertype;
}

int Oper::getPriority() {
    return PRIORITY[opertype];
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
        return new Number(number);
}

Lexem *get_oper(std::string codeline, int & pos) {
    int size = sizeof(OPERTEXT) / sizeof(std::string);
    for (int i = 0; i < size; i++) {
        int opsize = OPERTEXT[i].size();
        if(codeline.substr(pos, opsize) == OPERTEXT[i]) {
            pos += opsize;
            return new Oper(i);
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
    std::string var;
    for (int i = pos; i <= size; i++) {
        if (!checkWord(codeline[pos])) {
            var = codeline.substr(pos, i - pos);
            pos = i - 1;
            if(_map.find(var) == _map.end()){
                _map[var] = 0;
                return nullptr;
            }
        }
    }
    return new Variable(var);
}

std::vector<Lexem *> parseLexem(std::string codeline){
    std::vector<Lexem *> infix;
    Lexem *lexem = NULL;
    for (int i = 0, size = codeline.size(); i < size;) {
        while ((codeline[i] == ' ') || (codeline[i] == '\t') || (codeline[i] == '\n'))
            i++;
            if (!lexem)
            lexem = get_number(codeline, i);
            if (!lexem)
            lexem = get_oper(codeline, i);
            if (!lexem)
            lexem = get_var(codeline, i);
            if (lexem) {
                infix.push_back(lexem);
                lexem = nullptr;
            } else
                i++;
                }
    return infix;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix){
    std::vector<Lexem *> poliz;
    std::stack<Lexem *> opstack;

    for (int i = 0, size = infix.size(); i < size; i++) {
        LEXTYPE lextype = infix[i]->getLexType();
        switch(lextype) {
            case NUMBER:
                poliz.push_back(infix[i]);
                break;
            case VARIABLE:
                poliz.push_back(infix[i]);
                break;
            case OPER:
                switch((infix[i])->getType()) {
                    case LBRACKET:
                        opstack.push(infix[i]);
                        break;
                    case RBRACKET:
                        delete infix[i];
                        while ((opstack.top())->getType() != LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        delete opstack.top();
                        opstack.pop();
                        break;
                    default:
                        while ((!opstack.empty()) && (opstack.top())->getPriority() >= (infix[i])->getPriority()){
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.push(infix[i]);
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
    return evalstack.top()->getValue();
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
        std::cout << value << std::endl;
  }
  return 0;
}
