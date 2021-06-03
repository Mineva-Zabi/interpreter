#include <semantic.h>


int evaluatePoliz(const std::vector<Lexem *> &poliz, int row) {
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
                if (poliz[i]->getType() == PRINT) {
    				std::cout << "PRINT: " << evalstack.top() -> getValue();
    				break;
			    }
                std::cout << "oper" << std::endl;
                if (poliz[i]->getType() == GOTO || poliz[i]->getType() == ELSE ||
                    poliz[i]->getType() == ENDWHILE) {
                    Goto *lexemgoto = (Goto*)(poliz[i]);
                    //std::cout << lexemgoto->getRow() << std::endl;
                    return lexemgoto->getRow();
                } else if (poliz[i]->getType() == IF || poliz[i]->getType() == WHILE) {
				    Goto *lexemgoto = (Goto *)poliz[i];
				    Lexem *rvalue = evalstack.top();
				    evalstack.pop();
				    if (!(rvalue->getValue())) {
					    return lexemgoto->getRow();
				    }
				    continue;
                }
                right = evalstack.top();
                evalstack.pop();
                left = evalstack.top();
                evalstack.pop();
                if (poliz[i]->getType() == LVALUE) {
    				Lexem *arrayElem = new Array(opstack.top()->getName());
    				opstack.pop();
    				((Array *)arrayElem)->setIndex(l->getValue());
    				((Array *)arrayElem)->setValue(r->getValue());
    				recycle.push_back(arrayElem);
    				break;
			}
                ptr = new Number(poliz[i]->getValue(left, right);
                evalstack.push(ptr);
                recycle.push_back(ptr);
                break;
            }
            default: {}
        }
    }
    //int ev = evalstack.top() -> getValue();
    //delete evalstack.top();
    //std::cout << ev << std::endl;
    return row + 1;
}
