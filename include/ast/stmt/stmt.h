#ifndef STMT_H
#define STMT_H

#include "fwd.h"

class Stmt {
public:
    class Visitor {
    public:
        virtual void VisitExprStmt(ExprStmt*) = 0;
        virtual void VisitVarStmt(VarStmt*) = 0;
    };

    virtual void Accept(Stmt::Visitor*) = 0;
};

#endif /* STMT_H */
