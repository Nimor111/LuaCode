#ifndef VAR_STMT_H
#define VAR_STMT_H

#include "../expr/expr.h"
#include "stmt.h"

class VarStmt : public Stmt {
private:
    Token name_;
    Expr* value_;

public:
    VarStmt(Token, Expr*);

    virtual void Accept(Stmt::Visitor*) override;

    Expr* value() const;
    Token name() const;
};

#endif /* VAR_STMT_H */
