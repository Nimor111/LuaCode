#include "../include/error.h"

bool Error::had_error_ = false;

void Error::set_had_error(bool had_error)
{
    Error::had_error_ = had_error;
}

bool Error::had_error()
{
    return Error::had_error_;
}

void Error::MakeError(int line, std::string message)
{
    Error::Report(line, "", message);
}

void Error::MakeError(Token token, std::string message)
{
    if (token.type() == T_EOF) {
        Error::Report(token.line(), "at end", message);
    } else {
        Error::Report(token.line(), std::string("at '") + token.lexeme() + std::string("'"), message);
    }
}

void Error::Report(int line, std::string location, std::string message)
{
    std::cerr << "[line " << line << "] Error " << location << ": " << message << std::endl;
    Error::had_error_ = true;
}
