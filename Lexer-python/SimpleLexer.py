from Token import TokenType
from DFA import DfaState


class SimpleToken:
    def __init__(self, type: TokenType = None) -> None:
        self.type: TokenType = type
        self.text: str = str()

    def getType(self) -> TokenType:
        return self.type

    def getText(self) -> str:
        return self.text

    def __repr__(self) -> str:
        return "{" + self.text + ": " + str(self.type) + "}"


class SimpleLexer:
    def __init__(self) -> None:
        self.tokenText: str = str()
        self.tokens: list[SimpleToken] = list()
        self.token = SimpleToken()

    def initToken(self, ch: str) -> DfaState:

        if len(self.tokenText) > 0:
            self.token.text = self.tokenText
            self.tokens.append(self.token)
            self.tokenText = str()
            self.token = SimpleToken()

        newState: DfaState = DfaState.Initial

        if ch.isalpha():
            if ch == 'i':
                newState = DfaState.Id_int1
            else:
                newState = DfaState.Id
            self.token.type = TokenType.Identifier
            self.tokenText += ch

        elif ch.isdigit():
            newState = DfaState.IntLiteral
            self.token.type = TokenType.IntLiteral
            self.tokenText += ch

        elif ch == '>':
            newState = DfaState.GT
            self.token.type = TokenType.GT
            self.tokenText += ch

        elif ch == '+':
            newState = DfaState.Plus
            self.token.type = TokenType.Plus
            self.tokenText += ch

        elif ch == '-':
            newState = DfaState.Minus
            self.token.type = TokenType.Minus
            self.tokenText += ch

        elif ch == '*':
            newState = DfaState.Star
            self.token.type = TokenType.Star
            self.tokenText += ch

        elif ch == '/':
            newState = DfaState.Slash
            self.token.type = TokenType.Slash
            self.tokenText += ch

        elif ch == '(':
            newState = DfaState.LeftParen
            self.token.type = TokenType.LeftParen
            self.tokenText += ch

        elif ch == ')':
            newState = DfaState.RightParen
            self.token.type = TokenType.RightParen
            self.tokenText += ch

        elif ch == '=':
            newState = DfaState.Assignment
            self.token.type = TokenType.Assignment
            self.tokenText += ch
        else:
            newState = DfaState.Initial

        return newState

    def tokenize(self, code: str):

        state = DfaState.Initial
        for ch in code:
            if state == DfaState.Initial:
                state = self.initToken(ch)
                continue
            elif state == DfaState.Id:
                if ch.isalpha() or ch.isdigit():
                    self.tokenText += ch
                else:
                    state = self.initToken(ch)
                continue
            elif state == DfaState.Assignment:
                state = self.initToken(ch)

            elif state == DfaState.IntLiteral:
                if ch.isdigit():
                    self.tokenText += ch
                else:
                    state = self.initToken(ch)
                continue

            elif state == DfaState.Id_int1:
                if ch == 'n':
                    state = DfaState.Id_int2
                    self.tokenText += ch
                elif ch.isalpha() or ch.isdigit():
                    state = DfaState.Id
                    self.tokenText += ch
                else:
                    state = self.initToken(ch)
                    continue
            elif state == DfaState.Id_int2:
                if ch == 'n':
                    state = DfaState.Id_int3
                    self.tokenText += ch
                elif ch.isalpha() or ch.isdigit():
                    state = DfaState.Id
                    self.tokenText += ch
                else:
                    state = self.initToken(ch)
                continue
            elif state == DfaState.Id_int3:
                if ch.isspace():
                    state = DfaState.Int
                    state = self.initToken(ch)
                else:
                    state = DfaState.Id
                    self.tokenText += ch
                continue
            else:
                continue

        if len(self.tokenText) > 0:
            self.initToken('0')
        return self.tokens

if __name__ == "__main__":
    lexer = SimpleLexer()
    code = "int age = 45"
    lexer.tokenize(code)
    print(lexer.tokens)

