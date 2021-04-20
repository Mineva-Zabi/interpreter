#include <lexem.h>
#include <lexical.h>
#include <semantic.h>
#include <syntax.h>



int main() {
    std::string codeline;
    std::vector <std::vector<Lexem *>> infixLines;
    std::vector <std::vector<Lexem *>> postfixLines;


    while (std::getline(std::cin, codeline) && codeline != "exit") {
        infixLines.push_back(parseLexem(codeline));
    }
    for (int row = 0; row < (int)infixLines.size(); ++row)
        initLabels(infixLines[row], row);
        
    for (const auto &infix: infixLines)
        postfixLines.push_back(buildPoliz(infix));

    int row = 0;
    while (row >= 0 && row < (int)postfixLines.size())
        row = evaluatePoliz(postfixLines[row], row);
    std::cout << std::endl;
    printVar();
    std::cout << std::endl;
    printLabel();
    return 0;
}
