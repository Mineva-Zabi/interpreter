#include <lexem.h>
#include <lexical.h>
#include <semantic.h>
#include <syntax.h>

std::map<std::string, int> varTable;

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
        std::cout << "Value: " << value << std::endl;
        printVar();
        std::cout << std::endl;
  }
  return 0;
}
