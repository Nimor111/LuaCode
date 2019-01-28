#ifndef VISITOR_H
#define VISITOR_H

#include "fwd.h"

class Visitor {
public:
    virtual void VisitBinExpr(BinExpr*) = 0;
    virtual void VisitUnaryExpr(UnaryExpr*) = 0;
    virtual void VisitNumberExpr(NumberExpr*) = 0;
};

#endif /* VISITOR_H */
