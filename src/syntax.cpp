#include <syntax.h>


std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix) {
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
                Variable *lexemvar = (Variable*)(infix[i]);
                if (lexemvar->inLabelsMap()){
                        //std::cout << "yes" << std::endl;
                    joinGotoAndLabel(lexemvar, opstack);
                } else {
                    poliz.push_back(infix[i]);
                }
                break;
            }
            case OPER: {
                switch(infix[i]->getType()) {
                    case GOTO: {
                        while (!opstack.empty()) {
                            poliz.push_back(opstack.top());
                            opstack.pop();
                        }
                    }
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
                    while ((opstack.size() > 0) && ((opstack.top())->getPriority() >= infix[i]->getPriority())){
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

void joinGotoAndLabel(Variable *lexemvar, std::stack<Lexem *> &stack) {
    if (stack.top()->getType() == GOTO) {
        Goto *lexemgoto = (Goto*)stack.top();
        lexemgoto->setRow(labelsMap[lexemvar->getName()]);
    }
}
