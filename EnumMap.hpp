#ifndef __ENUM_MAP__
#define __ENUM_MAP__

#include <map>
#include <string>
#include "Token.hpp"
#include "DFA.hpp"

std::map<TokenType, std::string> type_to_string{

    {TokenType::Plus, "Plus"},   // +
    {TokenType::Minus, "Minus"}, // -
    {TokenType::Star, "Star"},   // *
    {TokenType::Slash, "Slash"}, // /

    {TokenType::GE, "GE"}, // >=
    {TokenType::GT, "GT"}, // >
    {TokenType::EQ, "EQ"}, // ==
    {TokenType::LE, "LE"}, // <=
    {TokenType::LT, "LT"}, // <

    {TokenType::SemiColon, "SemiColon"},   // ;
    {TokenType::LeftParen, "LeftParen"},   // (
    {TokenType::RightParen, "RightParen"}, // )
    {TokenType::Assignment, "Assignment"}, // =

    {TokenType::If, "If"},
    {TokenType::Else, "Else"},

    {TokenType::Int, "Int"},
    {TokenType::Identifier, "Identifier"},       //标识符
    {TokenType::IntLiteral, "IntLiteral"},       //整型字面量
    {TokenType::StringLiteral, "StringLiteral"}, //字符串字面量
    {TokenType::Space, "Space"}                  //空格
};

#endif