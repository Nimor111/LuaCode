#ifndef EXPR_H
#define EXPR_H

#include "../token.h"
#include "visitor.h"

class Expr {
public:
    virtual void Accept(Visitor* visitor) = 0;
};

#endif /* EXPR_H */
