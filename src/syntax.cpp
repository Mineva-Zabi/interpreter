#include <syntax.h>


std::vector<Lexem*> buildPoliz(std::vector<Lexem*> infix) {
    std::vector<Lexem *> poliz;
    std::stack<Lexem *> operStack;
    int LvalueFlag = 0;
    for(auto currentLexem: infix) {
        if(currentLexem == nullptr) {
            continue;
        }
        switch(currentLexem -> getLexType()) {

            case NUMBER: {
                poliz.push_back(currentLexem);
                break;
            }
            case VARIABLE: {
                Variable *lexemvar = (Variable*)currentLexem;
                if(((Variable*)currentLexem) -> inLabelsMap()) {
                    joinGotoAndLabel(lexemvar, poliz);
                    break;
                }
                poliz.push_back(currentLexem);
                break;
            }
            case OPER: {
                int oper = currentLexem -> getType();
                switch(oper) {
                    case GOTO: {
                        while (!operStack.empty()) {
                            poliz.push_back(operStack.top());
                            operStack.pop();
                        }
                        poliz.push_back(currentLexem);
                        break;
                    }
                    case ENDIF: {
                        break;
                    }
                    case LBRACKET: {
                        operStack.push(currentLexem);
                        break;
                    }
                    case LVALUE:
				        LvalueFlag = 1;
        				tmp = (Oper *)infix[i];
        			case RVALUE:
        				opstack.push((Oper *)infix[i]);
                    case LBRACKET:
    				    opstack.push((Oper *)infix[i]);
    				    break;
    			    case RSQUBR:
                    case RBRACKET:
        				while (opstack.top()->getType() != LBRACKET and opstack.top()->getType() != LVALUE and
                				opstack.top()->getType() != RVALUE) {
        					postfix.push_back(opstack.top());
        					opstack.pop();
    				    }
				if(opstack.top()->getType() == RVALUE) {
					postfix.push_back(opstack.top());
				}
				opstack.pop();
                    default: {}
                }
                if (!operStack.empty()){
                    while(!operStack.empty() && (operStack.top() -> getPriority() >= currentLexem -> getPriority())) {
                        poliz.push_back(operStack.top());
                        operStack.pop();
                    }
                }
                operStack.push(currentLexem);
            }
            default: {}
        }
    }
    while(!operStack.empty()) {
        poliz.push_back(operStack.top());
        operStack.pop();
    }
    return poliz;
}

void joinGotoAndLabel(Variable *lexemvar, std::vector<Lexem *> vec) {
    std::cout << "before join" << std::endl;
    if (vec.back()->getType() == GOTO) {
        Goto *lexemgoto = (Goto*)(vec.back());
        lexemgoto->setRow(lexemvar->getName());
        std::cout << "join" << std::endl;
    }

}
