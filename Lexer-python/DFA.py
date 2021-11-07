from enum import Enum
class DfaState(Enum):

    Initial=1

    If=2
    Id_if1=3
    Id_if2=4
    Else=5
    Id_else1=6
    Id_else2=7
    Id_else3=8
    Id_else4=9
    Int=10
    Id_int1=11
    Id_int2=12
    Id_int3=13
    Id=14
    GT=15
    GE=16

    Assignment=17

    Plus=18
    Minus=19
    Star=20
    Slash=21

    SemiColon=22
    LeftParen=23
    RightParen=24

    IntLiteral=25
