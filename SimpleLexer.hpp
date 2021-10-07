#include <string>
#include <vector>
#include "TokenType.hpp"

class SimpleToken
{
public:
    TokenType getType()
    {
        return type;
    }
    std::string getText()
    {
        return text;
    }

private:
    TokenType type;
    std::string text;
};

class SimpleTokenReader
{
public:
    SimpleTokenReader(std::vector<SimpleToken *> tokens) : tokens(tokens) {}

    SimpleToken *read()
    {
        if (pos < tokens.size())
            return tokens[pos++];
        return nullptr;
    }
    SimpleToken *peek()
    {
        if (pos < tokens.size())
            return tokens[pos];
        return nullptr;
    }
    void unread()
    {
        if (pos > 0)
            pos--;
    }
    int getPosition() { return pos; }

    void setPosition(int position)
    {
        if (position >= 0 && position < tokens.size())
            pos = position;
    }

private:
    std::vector<SimpleToken *> tokens;
    int pos = 0;
};

class SimpleLexer
{

public:

private:
    std::string tokenText;
    std::vector<SimpleToken *> tokens;
    SimpleToken *token;

    enum DfaState
    {
        Initial,

        If,
        Id_if1,
        Id_if2,
        Else,
        Id_else1,
        Id_else2,
        Id_else3,
        Id_else4,
        Int,
        Id_int1,
        Id_int2,
        Id_int3,
        Id,
        GT,
        GE,

        Assignment,

        Plus,
        Minus,
        Star,
        Slash,

        SemiColon,
        LeftParen,
        RightParen,

        IntLiteral
    };
};
