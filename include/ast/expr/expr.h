#ifndef EXPR_H
#define EXPR_H

#include "../../scanner/token.h"
#include "fwd.h"

class Expr {
public:
    class Visitor {
    public:
        virtual void VisitBinExpr(BinExpr*) = 0;
        virtual void VisitUnaryExpr(UnaryExpr*) = 0;
        virtual void VisitNumberExpr(NumberExpr*) = 0;
        virtual void VisitStringExpr(StringExpr*) = 0;
        virtual void VisitGroupingExpr(GroupingExpr*) = 0;
        virtual void VisitLiteralExpr(LiteralExpr*) = 0;
        virtual void VisitVarExpr(VarExpr*) = 0;
    };

    virtual void Accept(Expr::Visitor* visitor) = 0;
    virtual void Print() = 0;
    virtual ~Expr() {};
};

#endif /* EXPR_H */
