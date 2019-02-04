#ifndef EXPR_H
#define EXPR_H

#include "../../scanner/token.h"
#include "visitor.h"

class Expr {
public:
    virtual void Accept(Visitor* visitor) = 0;
    virtual void Print() = 0;
    virtual ~Expr() {};
};

#endif /* EXPR_H */
