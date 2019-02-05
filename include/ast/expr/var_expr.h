#ifndef VAR_EXPR_H
#define VAR_EXPR_H

#include "../../scanner/token.h"
#include "expr.h"

class VarExpr : public Expr {
private:
    Token name_;

public:
    VarExpr(Token);

    virtual void Accept(Expr::Visitor*) override;
    virtual void Print() override;

    Token name() const;
};

#endif /* VAR_EXPR_H */
