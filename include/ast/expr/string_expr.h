#ifndef STRING_EXPR_H
#define STRING_EXPR_H

#include "expr.h"
#include <string>

class StringExpr : public Expr {
private:
    std::string value_;

public:
    StringExpr(std::string);
    void Accept(Expr::Visitor* visitor) override;
    void Print() override;
    std::string value() const;
};

#endif /* STRING_EXPR_H */
