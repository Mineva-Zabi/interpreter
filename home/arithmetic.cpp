#include <iostream>
#include <string>
#include <stack>
#include <vector>

enum LEXTYPE {
  NUMBER, 
};

enum OPERATOR {
  LBRACKET , RBRACKET ,
  PLUS , MINUS ,
  MULTIPLY
};

int PRIORITY [] = {
  -1 , -1 ,
  0, 0,
  1
};

std::string OPERTEXT[] = {
  "(", ")",
  "+", "-",
  "*"
};
int OP_NUM = sizeof(PRIORITY) / sizeof(int);

class Lexem {
  LEXTYPE lxtp;
public:
  Lexem (LEXTYPE type): lxtp(type) {}
  LEXTYPE getLexType();
  virtual void print() {}
};

class Number: public Lexem {
  int value;
public:
  Number(int number): Lexem(NUMBER), value(number) {}
  int getValue() const;
  void print();
};

class Oper: public Lexem {
  OPERATOR opertype;
public:
  Oper(int op);
  OPERATOR getType();
  int getPriority();
  int getValue(const Number & left, const Number & right);
  void print();
};

LEXTYPE Lexem::getLexType(){
  return lxtp;
}



int Number::getValue() const {
  return value;
}

void Number::print() {
  std::cout << value << ' ';
}

Oper::Oper(int op) : Lexem(OPER) {
  opertype = (OPERATOR) op;
}

OPERATOR Oper::getType() {
  return opertype;
}

int Oper::getPriority() {
  return PRIORITY[opertype];
}

int Oper::getValue(const Number & left, const Number & right) {
  int res;
  switch (opertype) {
    case PLUS: {
      res = left.getValue() + right.getValue();
      break;
    }
    case MINUS: {
      res = left.getValue() - right.getValue();
      break;
    }
    case MULTIPLY: {
      res = left.getValue() * right.getValue();
      break;
    }
  }
  return res;
}

void Oper::print() {
  std::cout << OPERTEXT[opertype] << ' ';
}

void print_vector(std::vector<Lexem *> infix) {
  int size = infix.size();
  for (int i = 0; i < size; i++) {
    infix[i]->print();
    std::cout << " ";
  }
  std::cout << std::endl;
}

Number *get_number(std::string codeline, int & pos) {
  if (!isdigit(codeline[pos]))
    return NULL;
  int number = 0;
  for (int size = codeline.size(); pos < size && isdigit(codeline[pos]); pos++)
    number = number * 10 + codeline[pos] - '0';
  return new Number(number);
}

Oper *get_oper(std::string codeline, int & pos) {
  int size = sizeof(OPERTEXT) / sizeof(std::string);
  for (int i = 0; i < size; i++) {
    int opsize = OPERTEXT[i].size();
    if(codeline.substr(pos, opsize) == OPERTEXT[i]) {
      pos += opsize;
      return new Oper(i);
    }
  }
  return NULL;
}

std::vector<Lexem *> parseLexem(std::string codeline){
  std::vector<Lexem *> infix;
  Lexem *lexem = NULL;
  for (int i = 0, size = codeline.size(); i < size;) {
    while (codeline[i] == ' ')
      i++;
    if (!lexem)
      lexem = get_number(codeline, i);
    if (!lexem)
      lexem = get_oper(codeline, i);
    if (lexem) {
      infix.push_back(lexem);
      lexem = nullptr;
    } else
        i++;
  }
  return infix;
}

std::vector<Lexem *> buildPoliz(std::vector<Lexem *> infix){
  std::vector<Lexem *> poliz;
  std::stack<Lexem *> opstack;

  for (int i = 0, size = infix.size(); i < size; i++) {
    LEXTYPE lextype = infix[i]->getLexType();
    switch(lextype) {
      case NUMBER:
        poliz. push_back(infix[i]);
        break;
      case OPER:
        switch(((Oper*)infix[i])->getType()) {
          case LBRACKET:
            opstack.push(infix[i]);
            break;
          case RBRACKET:
            while (((Oper *)opstack.top())->getType() != LBRACKET) {
              poliz. push_back(opstack.top());
              opstack.pop();
          }
            opstack.pop();
            break;
          default:
            while ((!opstack.empty()) && ((Oper *)opstack.top())->getPriority() >= ((Oper*)infix[i])->getPriority()){
              poliz.push_back(opstack.top());
              opstack.pop();
          }
          opstack.push(infix[i]);
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

int evaluatePoliz(std::vector<Lexem *> poliz) {
  std::stack<Number *> evalstack;

  for (int i = 0, size = poliz. size(), right, left; i < size; i++) {
    switch(poliz[i]->getLexType()) {
      case NUMBER:
        evalstack.push((Number *)poliz[i]);
        break;
      case OPER:
        right = evalstack.top()->getValue();
        evalstack.pop();
        left = evalstack.top()->getValue();
        evalstack.pop();
        evalstack.push(new Number(((Oper*)poliz[i])->getValue(Number(left), Number(right))));
        break;
      default: {}
    }
  }
  return evalstack.top()->getValue();
}

int main() {
  std::string codeline;
  std::vector <Lexem *> infix;
  std::vector <Lexem *> postfix;
  int value;

  while (std::getline(std::cin, codeline)) {
    // " 10+2 " -> [10 ,+ ,2]
    infix = parseLexem(codeline);
    //[10 ,+ ,2] -> [10 , 2 , +]
    postfix = buildPoliz(infix);
    //[10 , 2 , +] -> 12
    value = evaluatePoliz(postfix);
    std::cout << value << std::endl;
  }
return 0;
}
