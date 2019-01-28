#include "../../include/ast/number_expr.h"

NumberExpr::NumberExpr(double number)
    : number_(number)
{
}

void NumberExpr::Accept(Visitor* visitor)
{
    visitor->VisitNumberExpr(this);
}

double NumberExpr::number() const
{
    return this->number_;
}
