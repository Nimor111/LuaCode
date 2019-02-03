#include "../../include/ast/ast_printer.h"

inline const std::string boolToString(int value)
{
    return value == -1 ? "nil" : value == 0 ? "false" : "true";
}

void AstPrinter::Print(Expr* expr)
{
    expr->Accept(this);
}

void AstPrinter::VisitBinExpr(BinExpr* binExpr)
{
    std::vector<Expr*> exprs = { binExpr->left(), binExpr->right() };
    parenthesize(binExpr->op().lexeme(), exprs);
}

void AstPrinter::VisitUnaryExpr(UnaryExpr* unaryExpr)
{
    std::vector<Expr*> exprs = { unaryExpr->right() };
    parenthesize(unaryExpr->op().lexeme(), exprs);
}

void AstPrinter::VisitNumberExpr(NumberExpr* numberExpr)
{
    std::vector<Expr*> exprs;
    parenthesize(std::to_string(numberExpr->number()), exprs);
}

void AstPrinter::VisitStringExpr(StringExpr* stringExpr)
{
    std::vector<Expr*> exprs;
    parenthesize(stringExpr->value(), exprs);
}

void AstPrinter::VisitGroupingExpr(GroupingExpr* groupingExpr)
{
    std::vector<Expr*> exprs = { groupingExpr->Expr() };
    parenthesize("group", exprs);
}

void AstPrinter::VisitLiteralExpr(LiteralExpr* literalExpr)
{
    std::vector<Expr*> exprs;
    parenthesize(boolToString(literalExpr->value()), exprs);
}

void AstPrinter::parenthesize(std::string lexeme, std::vector<Expr*> exprs)
{
    std::cout << "(" << lexeme;
    for (auto const& expr : exprs) {
        std::cout << " ";
        expr->Accept(this);
    }

    std::cout << ")";
}
