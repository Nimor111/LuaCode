#include "../../include/ast/unary_expr.h"

UnaryExpr::UnaryExpr(Token op, Expr* right)
    : right_(right)
    , op_(op)
{
}

void UnaryExpr::Accept(Visitor* visitor)
{
    visitor->VisitUnaryExpr(this);
}

Expr* UnaryExpr::right() const
{
    return this->right_;
}

Token UnaryExpr::op() const
{
    return this->op_;
}
