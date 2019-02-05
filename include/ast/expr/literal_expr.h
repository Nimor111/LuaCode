#ifndef LITERAL_EXPR_H
#define LITERAL_EXPR_H

#include "./expr.h"

class LiteralExpr : public Expr {
private:
    int value_;

public:
    LiteralExpr(int);
    void Accept(Expr::Visitor* visitor) override;
    void Print() override;

    int value() const;
};

#endif /* LITERAL_EXPR_H */
