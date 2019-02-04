#include "../../../include/ast/expr/grouping_expr.h"

GroupingExpr::GroupingExpr(class Expr* expr)
    : expr_(expr)
{
}

void GroupingExpr::Print()
{
    this->expr_->Print();
}

Expr* GroupingExpr::Expr()
{
    return this->expr_;
}

void GroupingExpr::Accept(Visitor* visitor)
{
    visitor->VisitGroupingExpr(this);
}
