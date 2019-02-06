#ifndef GROUPING_EXPR_H
#define GROUPING_EXPR_H

#include "expr.h"

class GroupingExpr : public Expr {
private:
    Expr* expr_;

public:
    GroupingExpr(Expr*);
    void Accept(Expr::Visitor*) override;
    void Print() override;
    Expr* Expr();
};

#endif /* GROUPING_EXPR_H */
