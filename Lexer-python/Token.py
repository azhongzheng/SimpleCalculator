from enum import Enum


class TokenType(Enum):
    Plus = 1
    Minus = 2
    Star = 3
    Slash = 4

    GE = 5
    GT = 6
    EQ = 7
    LE = 8
    LT = 9

    SemiColon = 10
    LeftParen = 11
    RightParen = 12

    Assignment = 13

    If = 14
    Else = 15

    Int = 16

    Identifier = 17

    IntLiteral = 18
    StringLiteral = 19
    Space = 10
