#include <lexical.h>





Lexem *getNumber(std::string codeline, int & pos) {
    if (!isdigit(codeline[pos]))
        return NULL;
    int number = 0;
    for (int size = codeline.size(); pos < size && isdigit(codeline[pos]); pos++)
        number = number * 10 + codeline[pos] - '0';
    pos--;
    return new Number(number);
}

Lexem *getOper(std::string codeline, int & pos) {
    for (int i = 0; i < OP_NUM; i++) {
        std::string subcodeline = codeline.substr(pos, OPERTEXT[i].size());
        if (OPERTEXT[i] == subcodeline) {
            pos += OPERTEXT[i].size() - 1;
            if ( i == GOTO || i == IF ||i == ELSE ||
                   i == WHILE || i == ENDWHILE )
                    return new Goto(static_cast<OPERATOR>(i));
            else if (j == LSQUBR) {
                if (!Lbr) {
					Lbr = 1;
					ptr = new Oper(OPERTEXT[LVALUE]);
				} else {
					ptr = new Oper(OPERTEXT[RVALUE]);
				}
			} else {
				ptr = new Oper(OPERTEXT[j]);
			}
            return new Oper(subcodeline);
        }
    }
    return NULL;
}

Lexem *getVar(std::string codeline, int & i) {
    if (((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
        ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
        (codeline[i] == '_')) {
        std::string name = "";
        while ( (i < codeline.size()) and (
                ((codeline[i] >= 'a') and (codeline[i] <= 'z')) or
                ((codeline[i] >= 'A') and (codeline[i] <= 'Z')) or
                ((codeline[i] >= '1') and (codeline[i] <= '9')) or
                (codeline[i] == '_')
                )){
            name += codeline[i];
            i++;
        }
        i--;  // for correct incrementation
        return new Variable(name);
    if (varTable.find(name) == varTable.end()) {
            varTable[name] = 0;
        }
    }
    return NULL;
}

std::vector<Lexem *> parseLexem(std::string codeline) {
    std::vector<Lexem *> infix;
    for (int i = 0; i < codeline.size(); i++) {
        if ((codeline[i] == ' ') || (codeline[i] == '\t') || (codeline[i] == '\n'))
            continue;
        Lexem *lexem = NULL;
        lexem = getOper(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = getNumber(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
        lexem = getVar(codeline, i);
        if (lexem != NULL) {
            infix.push_back(lexem);
            continue;
        }
    }
    return infix;
}

void initLabels(std::vector <Lexem*> &infix, int row) {
    for (int i = 1; i < infix.size(); i++) {
        if (infix[i-1]->getLexType() == VARIABLE && infix[i]->getLexType() == OPER) {
            Variable *lexemvar = (Variable *)infix[i-1];
            Oper *lexemop = (Oper *)infix[i];
            if (lexemvar && lexemop){
                if (lexemop->getType() == COLON) {
                    labelsMap[lexemvar->getName()] = row;
                    delete infix[i-1];
                    delete infix[i];
                    infix[i-1] = nullptr;
                    infix[i] = nullptr;
                    i++;
                }
            }
        }
    }
}

void initJumps(std::vector< std::vector<Lexem *>> infix) {
	std::stack<Goto *> stackIfElse, stackWhile;
	for (int row = 0; row < infix.size(); row++) {
		for (int i = 0; i < infix[row].size(); i++) {
			if (infix[row][i] == nullptr) {
				continue;
			}
			if (infix[row][i] -> getLexType() == OPER) {
				switch (infix[row][i] -> getType()) {
					case IF:
						stackIfElse.push((Goto *)infix[row][i]);
						break;
					case ELSE:
						if (stackIfElse.empty()) {
							perror("empty stackIfelse wrong syntax: else");
							exit(1);
						}
						stackIfElse.top() -> setRow(row + 1);
						stackIfElse.pop();
						stackIfElse.push((Goto *)infix[row][i]);
						break;
					case ENDIF:
						if (stackIfElse.empty()) {
							perror("empty stackIfelse wrong syntax: endif");
							exit(1);
						}
						stackIfElse.top() -> setRow(row + 1);
						stackIfElse.pop();
						break;
					case WHILE:
						((Goto *)infix[row][i]) -> setRow(row);
						stackWhile.push((Goto *)infix[row][i]);
						break;
					case ENDWHILE:
						if (stackWhile.empty()) {
							perror("empty stackwhile wrong syntax: endwhile");
							exit(1);
						}
						((Goto *)infix[row][i]) -> setRow(stackWhile.top() -> getRow());
						stackWhile.top() -> setRow(row + 1);
						stackWhile.pop();
						break;
				}
			}
		}
	}
}
