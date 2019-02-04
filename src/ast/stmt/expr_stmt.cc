#include "../../../include/ast/stmt/expr_stmt.h"

ExprStmt::ExprStmt(Expr* expression)
    : expression_(expression)
{
}

void ExprStmt::Accept(Stmt::Visitor* visitor)
{
    visitor->VisitExprStmt(this);
}

Expr* ExprStmt::expr()
{
    return this->expression_;
}
