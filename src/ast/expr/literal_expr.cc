#include "../../../include/ast/expr/literal_expr.h"

LiteralExpr::LiteralExpr(int value)
    : value_(value)
{
}

void LiteralExpr::Accept(Visitor* visitor)
{
    visitor->VisitLiteralExpr(this);
}

void LiteralExpr::Print()
{
    std::cout << this->value_ << std::endl;
}

int LiteralExpr::value() const
{
    return this->value_;
}
