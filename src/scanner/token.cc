#include "../include/scanner/token.h"

Token::Token(TokenType type, std::string lexeme, Literal literal, int line)
    : type_(type)
    , lexeme_(lexeme)
    , literal_(literal)
    , line_(line)
{
}

bool Token::operator==(Token const& other) const
{
    return this->type_ == other.type_ && this->lexeme_ == other.lexeme_ && this->literal_ == other.literal_ && this->line_ == other.line_;
}

std::ostream& operator<<(std::ostream& os, Token const& token)
{
    if (token.type_ == NUMBER) {
        auto literal = std::get<double>(token.literal_);
        os << token.type_ << " " << token.lexeme_ << " " << literal << ": " << token.line_;
    } else {
        auto literal = std::get<std::string>(token.literal_);
        os << token.type_ << " " << token.lexeme_ << " " << literal << ": " << token.line_;
    }

    return os;
}

std::string Token::lexeme() const
{
    return this->lexeme_;
}

TokenType Token::type() const
{
    return this->type_;
}

Literal Token::literal() const
{
    return this->literal_;
}

int Token::line() const {
    return this->line_;
}
