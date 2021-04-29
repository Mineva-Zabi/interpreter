#include <semantic.h>


int evaluatePoliz(std::vector<Lexem *> poliz, int row) {
    std::stack<Lexem *> evalstack;
    Lexem *right, *left;

    for (int i = 0, size = poliz.size(); i < size; i++) {
        if (poliz[i] == nullptr)
            continue;
        switch(poliz[i]->getLexType()) {
            case NUMBER: {
                evalstack.push(poliz[i]);
                break;
            }
            case VARIABLE: {
                evalstack.push(poliz[i]);
                break;
            }
            case OPER: {
                std::cout << "qqqqqqqqq" << std::endl;
                if (poliz[i]->getType() == GOTO) {
                    Goto *lexemgoto = (Goto*)(poliz[i]);
                        std::cout << lexemgoto->getRow() << std::endl;
                    return lexemgoto->getRow();
                } else {
                    right = evalstack.top();
                    evalstack.pop();
                    left = evalstack.top();
                    evalstack.pop();
                    evalstack.push(new Number(poliz[i]->getValue(left, right)));
                    delete poliz[i];
                    delete left;
                    delete right;
                }
                break;
            }
            default: {}
        }
    }
    int ev = evalstack.top() -> getValue();
    delete evalstack.top();
    std::cout << ev << std::endl;
    return row + 1;
}
