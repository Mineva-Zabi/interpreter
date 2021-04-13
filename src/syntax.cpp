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
