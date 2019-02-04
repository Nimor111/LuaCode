#include "../../../include/ast/expr/bin_expr.h"

BinExpr::BinExpr(Expr* left, Token op, Expr* right)
    : left_(left)
    , op_(op)
    , right_(right)
{
}

void BinExpr::Print()
{
    this->left_->Print();
    std::cout << this->op_ << std::endl;
    this->right_->Print();
}

void BinExpr::Accept(Visitor* visitor)
{
    visitor->VisitBinExpr(this);
}

Expr* BinExpr::left() const
{
    return this->left_;
}

Expr* BinExpr::right() const
{
    return this->right_;
}

Token BinExpr::op() const
{
    return this->op_;
}
