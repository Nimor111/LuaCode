#ifndef LITERAL_EXPR_H
#define LITERAL_EXPR_H

#include "./expr.h"
#include "./visitor.h"

class LiteralExpr : public Expr {
private:
    int value_;

public:
    LiteralExpr(int);
    void Accept(Visitor* visitor) override;
    void Print() override;

    int value() const;
};

#endif /* LITERAL_EXPR_H */
