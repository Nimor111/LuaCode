#include "../../include/ast/ast_printer.h"

inline const std::string boolToString(int value)
{
    return value == -1 ? "nil" : value == 0 ? "false" : "true";
}

void AstPrinter::Print(Stmt* exprStmt)
{
    exprStmt->Accept(this);
}

void AstPrinter::PrintExpr(Expr* expr)
{
    expr->Accept(this);
}

void AstPrinter::VisitBinExpr(BinExpr* binExpr)
{
    std::vector<Expr*> exprs = { binExpr->left(), binExpr->right() };
    std::cout << "{\"" << binExpr->op().lexeme() << "\": ";
    std::cout << "[";
    bool first = true;
    for (auto const& expr : exprs) {
        if (!first) {
            std::cout << ", ";
        }
        expr->Accept(this);
        first = false;
    }
    std::cout << "]";
    std::cout << "}";
}

void AstPrinter::VisitUnaryExpr(UnaryExpr* unaryExpr)
{
    std::cout << "{\"" << unaryExpr->op().lexeme() << "\": ";
    std::cout << "[";
    unaryExpr->right()->Accept(this);
    std::cout << "]";
    std::cout << "}";
}

void AstPrinter::VisitNumberExpr(NumberExpr* numberExpr)
{
    std::cout << numberExpr->number();
}

void AstPrinter::VisitStringExpr(StringExpr* stringExpr)
{
    std::cout << "\"" << stringExpr->value() << "\"";
}

void AstPrinter::VisitGroupingExpr(GroupingExpr* groupingExpr)
{
    std::cout << "{\"group\": ";
    PrintExpr(groupingExpr->Expr());
    std::cout << "}";
}

void AstPrinter::VisitLiteralExpr(LiteralExpr* literalExpr)
{
    std::cout << "\"" << boolToString(literalExpr->value()) << "\"";
}

void AstPrinter::VisitVarExpr(VarExpr* varExpr)
{
    std::cout << "\"" << varExpr->name().lexeme() << "\"";
}

void AstPrinter::VisitExprStmt(ExprStmt* exprStmt)
{
    PrintExpr(exprStmt->expr());
}

void AstPrinter::VisitVarStmt(VarStmt* varStmt)
{
    std::cout << "{\"" << varStmt->name().lexeme() << "\": ";
    PrintExpr(varStmt->value());
    std::cout << "}";
}
