#include "SimpleLexer.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string script = "int age = 45";
    SimpleLexer lexer;
    auto tokens = lexer.tokenize(script);
    dump(SimpleTokenReader(tokens));
}
