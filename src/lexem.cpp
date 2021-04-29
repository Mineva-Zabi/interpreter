#include <lexem.h>

std::map<std::string, int> varTable;
std::map<std::string, int> labelsMap;
Lexem::Lexem(){}
LEXTYPE Lexem::getLexType(){
    return lxtp;
}
Lexem::Lexem(LEXTYPE type) {
    lxtp = type;
}
Lexem::~Lexem(){}
void Lexem::print() {}
OPERATOR Lexem::getType() {
    return PLUS;
}
int Lexem::getPriority(){
    return 1;
}
int Lexem::getValue() const {
    return 1;
}
void Lexem::setType(std::string) {}
int Lexem::getValue(Lexem*, Lexem*) const {
    return 1;
}
void Lexem::setValue(int){}

int Number::getValue() const {
    return value;
}


Number::~Number() {}
Number:: Number(){
    value = 0;
}

Number::Number(int number): Lexem(NUMBER), value(number) {}
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

Oper::Oper(OPERATOR op) {
    opertype = op;
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

Oper::Oper() {}
Oper::~Oper() {}

void Oper::setType(std::string op) {
    for (int i = 0; i < OP_NUM; i++) {
        if (op == OPERTEXT[i]) {
            opertype = (OPERATOR)(i);
            break;
        }
    }
}

int Variable::getValue() const {
    return varTable[name];
}

void Variable::setValue(int value_) {
    varTable[name] = value_;
}

Variable::Variable(){}
Variable::~Variable(){}
Variable::Variable(std::string str): Lexem(VARIABLE), name(str) {}


void Variable::print() {
    std::cout << name << '(' << varTable[name] << ')';
}

std::string Variable::getName() {
    return name;
}

Goto::Goto() {}

Goto::Goto(OPERATOR opertype) : Oper(opertype){
    row = INT32_MIN;
    oper = opertype;
}

void Goto::setRow(int row) {
    Goto::row = row;
}

void Goto::setRow(const std::string name) {
    row = labelsMap[name];
}

int Goto::getRow() {
    return row;
}

void Goto::print() {
    std :: cout << "[<row "<< row << ">" << oper << "]" ;
}

OPERATOR Goto::getType() {
    return oper;
}






void printVar() {
    std::cout << "VARIABLES TABLE:" << std::endl;
    for (std::map<std::string, int>::iterator it = varTable.begin(); it != varTable.end(); it++) {
        std::cout << (it->first) << ' ' << (it->second) << ' ' << std::endl;
    }
}

void printLabel() {
    std::cout << "LABELS MAP:" << std::endl;
    for (std::map<std::string, int>::iterator it = labelsMap.begin(); it != labelsMap.end(); it++) {
        std::cout << (it->first) << ' ' << (it->second) << ' ' << std::endl;
    }
}

void printVector(std::vector<Lexem *> infix) {
    int size = infix.size();
    for (int i = 0; i < size; i++) {
        if (infix[i] == nullptr)
            continue;
        infix[i]->print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void printVecVec(const std::vector<std::vector<Lexem *>> &infix) {
    for (int i = 0; i < (int)infix.size(); i++) {
        std::cout << i << ": ";
        printVector(infix[i]);
    }
}

bool Variable::inLabelsMap() {
    if (labelsMap.find(name) != labelsMap.end()) {
        return true;
    }
return false;
}
