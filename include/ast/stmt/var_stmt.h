#ifndef VAR_STMT_H
#define VAR_STMT_H

#include "../expr.h"
#include "stmt.h"

class VarStmt : public Stmt {
private:
    Token name_;
    Expr* value_;

public:
    VarStmt(Token, Expr*);

    virtual void Accept(Stmt::Visitor* visitor) override;

    Expr* value() const;
    Token name() const;
};

#endif /* VAR_STMT_H */
