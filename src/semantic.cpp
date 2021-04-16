#include <semantic.h>


int evaluatePoliz(std::vector<Lexem *> poliz, int row) {
    std::stack<Lexem *> evalstack;
    Lexem *right, *left;
    for (const auto &lexem: poliz) {
        switch(lexem->getLexType()) {
            case nullptr:
                return 0;
            case NUMBER:
                Number *lexemnum = (Number*)lexem;
                evalstack.push(lexemnum);
                break;
            case VARIABLE:
                Variable *lexemvar = (Variable*)lexem;
                evalstack.push(lexemvar);
                break;
            case OPER:
                Oper* lexemop = (Oper*)lexem;
                if (lexemop->getType() == GOTO) {
                    Goto *lexemgoto = (Goto*)lexemop;
                    return lexemgoto->getRow();
                } else {
                    right = evalstack.top();
                    evalstack.pop();
                    left = evalstack.top();
                    evalstack.pop();
                    evalstack.push(new Number(lexem->getValue(left, right)));
                    delete lexem;
                    delete left;
                    delete right;
                }
                break;
            default: {}
        }
    }
    //int ev = evalstack.top() -> getValue();
    //delete evalstack.top();
    return row + 1;
}
