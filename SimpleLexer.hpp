#include <vector>
#include <iostream>
// #include "TokenType::hpp"

namespace Token
{
    enum TokenType
    {
        Plus,  // +
        Minus, // -
        Star,  // *
        Slash, // /

        GE, // >=
        GT, // >
        EQ, // ==
        LE, // <=
        LT, // <

        SemiColon,  // ;
        LeftParen,  // (
        RightParen, // )

        Assignment, // =

        If,
        Else,

        Int,

        Identifier, //标识符

        IntLiteral,   //整型字面量
        StringLiteral //字符串字面量
    };
}

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

class SimpleToken
{
public:
    SimpleToken(Token::TokenType type) : type(type) {}
    SimpleToken() {}
    Token::TokenType getType()
    {
        return type;
    }
    std::string getText()
    {
        return text;
    }

    Token::TokenType type;
    std::string text;
};

class SimpleTokenReader
{
public:
    SimpleTokenReader(std::vector<SimpleToken *> tokens) : tokens(tokens) {}

    void read()
    {
        // if (pos < tokens.size())
        // {
        //     SimpleToken *tk = tokens.back();
        //     tokens.pop_back();
        //     // std::cout<< "tokens.size()" <<tokens.size() <<" ";
        //     return tk;
        // }
        std::cout << "text\t\ttype\n";
        for (auto token : tokens)
            std::cout << token->getText() << "\t\t" << token->getType() << std::endl;
        // return nullptr;
    }
    SimpleToken *peek()
    {
        if (pos < tokens.size())
            return tokens[pos];
        return nullptr;
    }

    std::vector<SimpleToken *> getTokens()
    {
        return tokens;
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

public:
    std::vector<SimpleToken *> tokens;
    int pos = 0;
};

class SimpleLexer
{

public:
    DfaState initToken(char ch)
    {
        if (tokenText.size() > 0)
        {
            // std::cout << "tokenText:" << tokenText << "\n";
            token->text = tokenText;
            tokens.push_back(token);
            tokenText = "";
            token = new SimpleToken();
        }

        // std::cout <<"size:" << tokens.size();
        // std::cout << ch;
        // std::string tokenText;
        // SimpleToken *token = new SimpleToken();

        DfaState newState = DfaState::Initial;

        if (isalpha(ch))
        { //第一个字符是字母
            if (ch == 'i')
            {
                newState = DfaState::Id_int1;
            }
            else
            {
                newState = DfaState::Id; //进入Id状态
            }
            token->type = Token::TokenType::Identifier;
            tokenText += ch;
        }
        else if (isdigit(ch))
        { //第一个字符是数字
            newState = DfaState::IntLiteral;
            token->type = Token::TokenType::IntLiteral;
            tokenText += ch;
        }
        else if (ch == '>')
        { //第一个字符是>
            newState = DfaState::GT;
            token->type = Token::TokenType::GT;
            tokenText += ch;
        }
        else if (ch == '+')
        {
            newState = DfaState::Plus;
            token->type = Token::TokenType::Plus;
            tokenText += ch;
        }
        else if (ch == '-')
        {
            newState = DfaState::Minus;
            token->type = Token::TokenType::Minus;
            tokenText += ch;
        }
        else if (ch == '*')
        {
            newState = DfaState::Star;
            token->type = Token::TokenType::Star;
            tokenText += ch;
        }
        else if (ch == '/')
        {
            newState = DfaState::Slash;
            token->type = Token::TokenType::Slash;
            tokenText += ch;
        }
        else if (ch == ';')
        {
            newState = DfaState::SemiColon;
            token->type = Token::TokenType::SemiColon;
            tokenText += ch;
        }
        else if (ch == '(')
        {
            newState = DfaState::LeftParen;
            token->type = Token::TokenType::LeftParen;
            tokenText += ch;
        }
        else if (ch == ')')
        {
            newState = DfaState::RightParen;
            token->type = Token::TokenType::RightParen;
            tokenText += ch;
        }
        else if (ch == '=')
        {
            newState = DfaState::Assignment;
            token->type = Token::TokenType::Assignment;
            tokenText += ch;
        }
        else
        {
            newState = DfaState::Initial; // skip all unknown patterns
        }
        return newState;
        // return newState;
    }

    SimpleTokenReader *tokenize(std::string code)
    {
        // tokens = std::vector<SimpleToken *>();
        tokenText = "";
        token = new SimpleToken();
        int ich = 0;
        char ch = 0;
        DfaState state = DfaState::Initial;
        for (int i = 0; i < code.size(); i++)
        {
            char ch = code[i];

            switch (state)
            {

            case Initial:
                state = initToken(ch);
                // std::cout << ch << " state: " << state << "\n";
                break;
            case Id:
                if (isalpha(ch) || isdigit(ch))
                {
                    tokenText += ch;
                }
                else
                {
                    state = initToken(ch);
                }
                break;
            case GT:
                if (ch == '=')
                {
                    token->type = Token::TokenType::GE;
                    state = DfaState::GE;
                    tokenText += ch;
                }
                else
                {
                    state = initToken(ch);
                }
            case GE:
            case Assignment:
            case Plus:
            case Minus:
            case Star:
            case Slash:
            case SemiColon:
            case LeftParen:
            case RightParen:
                state = initToken(ch); //退出当前状态，并保存Token
                break;
            case IntLiteral:
                if (isdigit(ch))
                {
                    tokenText += ch; //继续保持在数字字面量状态
                }
                else
                {
                    state = initToken(ch); //退出当前状态，并保存Token
                }
                break;
            case Id_int1:
                if (ch == 'n')
                {
                    state = DfaState::Id_int2;
                    tokenText += ch;
                }
                else if (isdigit(ch) || isalpha(ch))
                {
                    state = DfaState::Id; //切换回Id状态
                    tokenText += ch;
                }
                else
                {
                    state = initToken(ch);
                }
                break;
            case Id_int2:
                if (ch == 't')
                {
                    state = DfaState::Id_int3;
                    tokenText += ch;
                }
                else if (isdigit(ch) || isalpha(ch))
                {
                    state = DfaState::Id; //切换回id状态
                    tokenText += ch;
                }
                else
                {
                    state = initToken(ch);
                }
                break;
            case Id_int3:
                if (isblank(ch))
                {
                    token->type = Token::TokenType::Int;
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
        {
            initToken(ch);
        }
        // for(auto token: tokens)
        //     std::cout << token->getText() << "\t\t" << token->getType();
        return new SimpleTokenReader(tokens);
    }

    void dump(SimpleTokenReader *tokenReader)
    {
        tokenReader->read();
    }

public:
    std::string tokenText;
    std::vector<SimpleToken *> tokens;
    SimpleToken *token;
};
