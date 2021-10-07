#include "SimpleLexer.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    /* code */
    SimpleLexer lexer; 
    // std::cout << isblank('a');

    std::vector<int> a = {1,2,3,4,5,6};
    int pos = 0;
    std::cout << a[pos++] << "\n";
    std::cout << a[pos++] << "\n";
    return 0;
}
