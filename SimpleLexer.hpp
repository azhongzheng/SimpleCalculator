#ifndef __SIMPLELEXER__
#define __SIMPLELEXER__

#include <vector>
#include <string>
#include <iostream>
#include "EnumMap.hpp"

class SimpleToken
{
public:
    SimpleToken(TokenType type) : type(type) {}
    SimpleToken() {}
    TokenType getType() { return type; }
    std::string getText() { return text; }
    TokenType type;
    std::string text;
};

class SimpleLexer
{
public:
    DfaState initToken(char ch)
    {
        if (tokenText.size() > 0)
        {
            token->text = tokenText;
            tokens.push_back(token);
            tokenText = "";
            token = new SimpleToken();
        }
        DfaState newState = DfaState::Initial;
        if (isalpha(ch))
        {
            if (ch == 'i')
                newState = DfaState::Id_int1;
            else
                newState = DfaState::Id;
            token->type = TokenType::Identifier;
            tokenText += ch;
        }
        else if (isdigit(ch))
        {
            newState = DfaState::IntLiteral;
            token->type = TokenType::IntLiteral;
            tokenText += ch;
        }
        else if (ch == '>')
        { //第一个字符是>
            newState = DfaState::GT;
            token->type = TokenType::GT;
            tokenText += ch;
        }
        else if (ch == '+')
        {
            newState = DfaState::Plus;
            token->type = TokenType::Plus;
            tokenText += ch;
        }
        else if (ch == '-')
        {
            newState = DfaState::Minus;
            token->type = TokenType::Minus;
            tokenText += ch;
        }
        else if (ch == '*')
        {
            newState = DfaState::Star;
            token->type = TokenType::Star;
            tokenText += ch;
        }
        else if (ch == '/')
        {
            newState = DfaState::Slash;
            token->type = TokenType::Slash;
            tokenText += ch;
        }
        else if (ch == ';')
        {
            newState = DfaState::SemiColon;
            token->type = TokenType::SemiColon;
            tokenText += ch;
        }
        else if (ch == '(')
        {
            newState = DfaState::LeftParen;
            token->type = TokenType::LeftParen;
            tokenText += ch;
        }
        else if (ch == ')')
        {
            newState = DfaState::RightParen;
            token->type = TokenType::RightParen;
            tokenText += ch;
        }
        else if (ch == '=')
        {
            newState = DfaState::Assignment;
            token->type = TokenType::Assignment;
            tokenText += ch;
        }
        else
            newState = DfaState::Initial; // skip all unknown patterns
   
        return newState;
    }

    std::vector<SimpleToken *> tokenize(std::string code)
    {
        // int ich = 0;
        char ch = 0;
        DfaState state = DfaState::Initial;
        for (auto ch : code)
        {
            // std::cout << ch << " ";
            switch (state)
            {
            case DfaState::Initial:
                state = initToken(ch);
                // std::cout << ch << "\n";
                break;
            case DfaState::Id:
                if (isalpha(ch) || isdigit(ch))
                    tokenText += ch;
                else
                    state = initToken(ch);
                break;
            case DfaState::GE:
            case DfaState::Assignment:
            case DfaState::Plus:
            case DfaState::Minus:
            case DfaState::Star:
            case DfaState::Slash:
            case DfaState::SemiColon:
            case DfaState::LeftParen:
            case DfaState::RightParen:
                state = initToken(ch); //退出当前状态，并保存Token
                break;
            case DfaState::IntLiteral:
                if (isdigit(ch))
                    tokenText += ch;
                else
                    state = initToken(ch);
                break;
            case DfaState::Id_int1:
                if (ch == 'n')
                {
                    state = DfaState::Id_int1;
                    tokenText += ch;
                }
                else if (isdigit(ch) || isalpha(ch))
                {
                    state = DfaState::Id;
                    tokenText += ch;
                }
                else
                    state = initToken(ch);
                break;
            case DfaState::Id_int2:
                if (ch == 't')
                {
                    state = DfaState::Id_int3;
                    tokenText += ch;
                }
                else if (isdigit(ch) || isalpha(ch))
                {
                    state = DfaState::Id;
                    tokenText += ch;
                }
                else
                    state = initToken(ch);
                break;
            case DfaState::Id_int3:
                if (isblank(ch))
                {
                    state = DfaState::Int;
                    state = initToken(ch);
                }
                else
                {
                    state = DfaState::Id; //切换回Id状态
                    tokenText += ch;
                }
                break;
            default:
                break;
            }
        }
        if (tokenText.length() > 0)
            initToken(ch);
        return tokens;
    }

private:
    std::string tokenText;
    std::vector<SimpleToken *> tokens;
    SimpleToken *token = new SimpleToken();
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

void dump(SimpleTokenReader tokenReader)
{
    std::cout << "text\ttype\n";
    SimpleToken *token;
    while ((token = tokenReader.read()) != nullptr)
    {
        std::cout << token->getText() << "\t" << type_to_string[token->getType()] << std::endl;
    }
}
#endif