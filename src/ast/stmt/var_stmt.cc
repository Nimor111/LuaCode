#include "../../../include/ast/stmt/var_stmt.h"

VarStmt::VarStmt(Token name, Expr* value)
    : name_(name)
    , value_(value)
{
}

void VarStmt::Accept(Stmt::Visitor* visitor)
{
    visitor->VisitVarStmt(this);
}

Expr* VarStmt::value() const
{
    return this->value_;
}

Token VarStmt::name() const
{
    return this->name_;
}
