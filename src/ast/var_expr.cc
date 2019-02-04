#include "../../include/ast/var_expr.h"

VarExpr::VarExpr(Token name)
    : name_(name)
{
}

void VarExpr::Accept(Visitor* visitor)
{
    visitor->VisitVarExpr(this);
}

void VarExpr::Print()
{
    std::cout << this->name_.lexeme() << std::endl;
}

Token VarExpr::name() const
{
    return this->name_;
}
