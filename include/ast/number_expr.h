#ifndef NUMBER_EXPR_H
#define NUMBER_EXPR_H

#include "expr.h"

class NumberExpr : public Expr {
private:
    double number_;

public:
    NumberExpr(double);
    void Accept(Visitor* visitor) override;
    double number() const;
};

#endif /* NUMBER_EXPR_H */
