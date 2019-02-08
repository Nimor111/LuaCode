#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "expr/bin_expr.h"
#include "expr/grouping_expr.h"
#include "expr/literal_expr.h"
#include "expr/number_expr.h"
#include "expr/string_expr.h"
#include "expr/unary_expr.h"
#include "expr/var_expr.h"
#include "stmt/expr_stmt.h"
#include "stmt/var_stmt.h"
#include <iostream>
#include <string>
#include <vector>

class AstPrinter : public Expr::Visitor, public Stmt::Visitor {
private:
    void parenthesize(std::string, std::vector<Expr*>);

public:
    void VisitBinExpr(BinExpr*) override;
    void VisitUnaryExpr(UnaryExpr*) override;
    void VisitNumberExpr(NumberExpr*) override;
    void VisitStringExpr(StringExpr*) override;
    void VisitGroupingExpr(GroupingExpr*) override;
    void VisitLiteralExpr(LiteralExpr*) override;
    void VisitVarExpr(VarExpr*) override;

    void VisitExprStmt(ExprStmt*) override;
    void VisitVarStmt(VarStmt*) override;
    void Print(Stmt*);
    void PrintExpr(Expr*);

    void PrintProgram(std::vector<Stmt*> const& );
};

#endif /* AST_PRINTER_H */
