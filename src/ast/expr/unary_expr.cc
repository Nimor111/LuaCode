#include "../../../include/ast/expr/unary_expr.h"

UnaryExpr::UnaryExpr(Token op, Expr* right)
    : right_(right)
    , op_(op)
{
}

void UnaryExpr::Print()
{
    std::cout << this->op_ << std::endl;
    this->right_->Print();
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
