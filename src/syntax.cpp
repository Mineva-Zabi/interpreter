#include <syntax.h>


std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
    std::vector<Lexem *> poliz;
    std::stack<Lexem *> opstack;

    for (const auto lexem: infix) {
        LEXTYPE lextype = lexem->getLexType();
        switch(lextype) {
            case nullptr:
            case NUMBER: {
                poliz.push_back(lexem);
                break;
            }
            case VARIABLE: {
                Variable *levemvar = (Variable*)lexem;
                if (lexemvar->inLabelsMap()){
                    joinGotoAndLabel(lexemvar, opstack);
                } else {
                    poliz.push_back(lexem);
                }
                break;
            }
            case OPER: {
                switch(lexem)->getType()) {
                    case LBRACKET: {
                        opstack.push(lexem);
                        break;
                    }
                    case RBRACKET: {
                        delete lexem;
                        while ((opstack.top())->getType() != LBRACKET) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        delete opstack.top();
                        opstack.pop();
                        break;
                    }
                    default: {}
                    while ((opstack.size() > 0) && ((opstack.top())->getPriority() >= lexem->getPriority())){
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                        opstack.push(lexem);
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

void joinGotoAndLabel(Variable *lexemvar, stack<Oper *> stack) {
    if (stack.top()->getType() == GOTO) {
        Goto *lexemgoto = (Goto*)stack.top();
        lexemgoto->setRow(labelsMap[lexemvar->getName()]);
    }
}
