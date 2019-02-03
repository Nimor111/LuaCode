#include "../../include/ast/string_expr.h"

StringExpr::StringExpr(std::string value)
    : value_(value)
{
}

void StringExpr::Print()
{
    std::cout << this->value_ << std::endl;
}

void StringExpr::Accept(Visitor* visitor)
{
    visitor->VisitStringExpr(this);
}

std::string StringExpr::value() const
{
    return this->value_;
}
