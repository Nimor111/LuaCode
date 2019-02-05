#ifndef EXPR_STMT_H
#define EXPR_STMT_H

#include "../expr/expr.h"
#include "stmt.h"

class ExprStmt : public Stmt {
private:
    Expr* expression_;

public:
    ExprStmt(Expr*);

    void Accept(Stmt::Visitor*) override;
    Expr* expr();
};

#endif /* EXPR_STMT_H */
