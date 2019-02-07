#ifndef RULES_H
#define RULES_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <vector>

#include "../ast/ast_printer.h"
#include "../ast/expr/expr.h"

using json = nlohmann::json;

template <typename T>
using vector = std::vector<T>;

void FindDeclarations(json, vector<std::string>&);
void FindVarExpressions(json, vector<std::string>&);

void UnusedVariables(Stmt*);
void UndefinedVariables(Stmt*);

#endif
