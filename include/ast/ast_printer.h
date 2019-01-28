#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "bin_expr.h"
#include "number_expr.h"
#include "unary_expr.h"
#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

class AstPrinter : public Visitor {
private:
    void parenthesize(std::string, std::vector<Expr*>);

public:
    void VisitBinExpr(BinExpr*) override;
    void VisitUnaryExpr(UnaryExpr*) override;
    void VisitNumberExpr(NumberExpr*) override;
    void Print(Expr*);
};

#endif /* AST_PRINTER_H */