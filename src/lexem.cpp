#include <lexem.h>


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

int Variable::getValue() const {
    return varTable[name];
}

void Variable::setValue(int value_) {
    varTable[name] = value_;
}

void Variable::print() {
    std::cout << name << '(' << varTable[name] << ')';
}

void printVar() {
    std::cout << "VARIABLES TABLE:" << std::endl;
    for (std::map<std::string, int>::iterator it = varTable.begin(); it != varTable.end(); it++) {
        std::cout << (it->first) << ' ' << (it->second) << ' ' << std::endl;
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
