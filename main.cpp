#include "SimpleLexer.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    /* code */
    // SimpleLexer *lexer = new SimpleLexer();
    // std::string script = "int age = 45;";
    // std::cout << "parse :" << script << std::endl;
    // SimpleTokenReader *tokenReader = lexer->tokenize(script);
    // lexer->dump(tokenReader);

    std::string script = "int age = 45";

    SimpleLexer lexer;
    auto tokens = lexer.tokenize(script);
    auto tokenreader = SimpleTokenReader(tokens);
    dump(tokenreader);
}
