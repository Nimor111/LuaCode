#include "../include/scanner.h"

std::map<std::string, TokenType> Scanner::keywords_ = {
    { "and", AND },
    { "break", BREAK },
    { "do", DO }, { "else", ELSE },
    { "elseif", ELSEIF },
    { "end", END },
    { "false", FALSE },
    { "for", FOR },
    { "function", FUNCTION },
    { "if", IF },
    { "in", IN },
    { "local", LOCAL },
    { "nil", NIL },
    { "not", NOT },
    { "or", OR },
    { "repeat", REPEAT },
    { "return", RETURN },
    { "then", THEN },
    { "true", TRUE },
    { "until", UNTIL },
    { "while", WHILE }
};

Scanner::Scanner(std::string source)
    : source_(source)
{
    this->start_ = 0;
    this->current_ = 0;
    this->line_ = 1;
}

std::vector<Token> Scanner::ScanTokens()
{
    while (!this->End()) {
        // Beginning of next lexeme
        this->start_ = this->current_;

        this->ScanToken();
    }

    this->tokens_.push_back(Token(T_EOF, "", std::string(""), this->line_));

    return this->tokens_;
}

bool Scanner::End(int ahead)
{
    return this->current_ + ahead >= int(this->source_.length());
}

void Scanner::ScanToken()
{
    char c = Advance();
    switch (c) {
    case '+':
        AddToken(PLUS);
        break;
    case '*':
        AddToken(MUL);
        break;
    case '/':
        AddToken(Match('/') ? FLOOR_DIV : DIV);
        break;
    case '%':
        AddToken(MOD);
        break;
    case '^':
        AddToken(POW);
        break;
    case '&':
        AddToken(BIT_AND);
        break;
    case '|':
        AddToken(BIT_OR);
        break;
    case '#':
        AddToken(LEN);
        break;
    case ';':
        AddToken(SEMICOLON);
        break;
    case ',':
        AddToken(COMMA);
        break;
    case ':':
        AddToken(COLON);
        break;
    case '(':
        AddToken(LEFT_PAREN);
        break;
    case ')':
        AddToken(RIGHT_PAREN);
        break;
    case '{':
        AddToken(LEFT_BRACE);
        break;
    case '}':
        AddToken(RIGHT_BRACE);
        break;
    case ']':
        AddToken(RIGHT_SQUARE);
        break;
    case '[':
        if (Match('[')) {
            MultiString();
        } else {
            AddToken(LEFT_SQUARE);
        }
        break;
    case '=':
        AddToken(Match('=') ? EQ : ASSIGN);
        break;
    case '~':
        if (Match('=')) {
            AddToken(DIFF);
        } else {
            AddToken(BIT_XOR);
        }
        break;
    case '>':
        if (Match('=')) {
            AddToken(GTE);
            break;
        } else if (Match('>')) {
            AddToken(RIGHT_SHIFT);
            break;
        }

        AddToken(GT);
        break;
    case '<':
        if (Match('=')) {
            AddToken(LTE);
            break;
        } else if (Match('<')) {
            AddToken(LEFT_SHIFT);
            break;
        }

        AddToken(Match('=') ? LTE : LT);
        break;
    case '.':
        AddToken(Match('.') ? Match('.') ? RANGE : CONCAT : DOT);
        break;
    case '-':
        if (Match('-')) {
            if (Match('[')) {
                if (Match('[')) {
                    MultiComment();
                    break;
                }
            }

            Comment();
            break;
        } else {
            AddToken(MINUS);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        this->line_++;
        break;
    case '"':
        String();
        break;
    default:
        if (isdigit(c)) {
            Number();
        } else if (Alpha(c)) {
            Identifier();
        } else {
            Error::MakeError(this->line_, std::string("Unexpected character: ") + this->source_[this->current_ - 1]);
        }
        break;
    }
}

char Scanner::Advance()
{
    this->current_++;

    return this->source_[this->current_ - 1];
}

void Scanner::AddToken(TokenType type)
{
    this->AddToken(type, std::string(""));
}

void Scanner::AddToken(TokenType type, Literal literal)
{
    std::string lexeme = this->source_.substr(this->start_, this->current_ - this->start_);
    this->tokens_.push_back(Token(type, lexeme, literal, this->line_));
}

bool Scanner::Match(char expected)
{
    if (this->End()) {
        return false;
    }

    if (this->source_[this->current_] != expected) {
        return false;
    }

    ++this->current_;

    return true;
}

std::string Scanner::Peek(int num)
{
    if (End(num)) {
        return "\0";
    }

    return this->source_.substr(this->current_, num + 1);
}

void Scanner::String()
{
    while (Peek() != std::string(1, '"') && !End()) {
        Advance();
    }

    if (End()) {
        Error::MakeError(this->line_, "Unterminated string.");
        return;
    }

    // The terminating ".
    Advance();

    // Trim quotes
    std::string value = this->source_.substr(this->start_ + 1, this->current_ - this->start_ - 2);

    AddToken(STRING, value);
}

void Scanner::MultiString()
{
    // TODO maybe support arbitrary amounts of ], though don't see the point
    while (Peek(1) != "]]" && !End(1)) {
        Advance();
    }

    if (End(1)) {
        Error::MakeError(this->line_, "Unterminated string.");
        return;
    }

    // Workaround
    Advance();
    Advance();

    std::string value = this->source_.substr(this->start_ + 2, this->current_ - this->start_ - 4);

    AddToken(STRING, value);
}

void Scanner::Number()
{
    while (isdigit(Peek()[0])) {
        Advance();
    }

    auto twoAhead = Peek(1);
    if (twoAhead.length() > 1 && twoAhead[0] == '.' && isdigit(twoAhead[1])) {
        Advance();

        while (isdigit(Peek()[0])) {
            Advance();
        }
    }

    AddToken(NUMBER, std::stod(this->source_.substr(this->start_, this->current_ - this->start_)));
}

bool Scanner::Alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

void Scanner::Identifier()
{
    while (Alpha(Peek()[0]) || isdigit(Peek()[0])) {
        Advance();
    }

    std::string ident = this->source_.substr(this->start_, this->current_ - this->start_);

    if (Scanner::keywords_.find(ident) != Scanner::keywords_.end()) {
        AddToken(Scanner::keywords_[ident]);
    } else {
        AddToken(IDENT);
    }
}

void Scanner::MultiComment()
{
    while (Peek(1) != std::string("]]") && !End()) {
        Advance();
    }

    if (End()) {
        Error::MakeError(this->line_, "Unterminated comment.");
    }

    Advance();
    Advance();
}

void Scanner::Comment()
{
    while (Peek() != std::string(1, '\n') && !End()) {
        Advance();
    }
}
