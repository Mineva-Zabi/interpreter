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
