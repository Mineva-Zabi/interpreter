#include <semantic.h>


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
