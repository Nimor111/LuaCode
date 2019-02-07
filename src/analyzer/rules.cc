#include "../../include/analyzer/rules.h"

void FindDeclarations(json object, vector<std::string>& v)
{
    for (auto const& el : object.items()) {
        auto key = el.key();
        if (key == "type" && object.at(key) == "VarDeclaration") {
            /* json j; */
            /* j["type"] = "VarDeclaration"; */
            /* j["name"] = object.at("name"); */
            v.push_back(object.at("name"));
        }

        if (std::all_of(key.begin(), key.end(), ::isdigit)) {
            if (object.at(std::stoi(key)).is_object() || object.at(std::stoi(key)).is_array()) {
                FindDeclarations(object.at(std::stoi(key)), v);
            }
        } else {
            if (object.at(key).is_object() || object.at(key).is_array()) {
                FindDeclarations(object.at(key), v);
            }
        }
    }
}

void FindVarExpressions(json object, vector<std::string>& v)
{
    for (auto const& el : object.items()) {
        auto key = el.key();
        if (key == "type" && object.at(key) == "VarName") {
            /* json j; */
            /* j["type"] = "VarExpression"; */
            /* j["value"] = object.at("value"); */
            v.push_back(object.at("value"));
        }

        if (std::all_of(key.begin(), key.end(), ::isdigit)) {
            if (object.at(std::stoi(key)).is_object() || object.at(std::stoi(key)).is_array()) {
                FindVarExpressions(object.at(std::stoi(key)), v);
            }
        } else {
            if (object.at(key).is_object() || object.at(key).is_array()) {
                FindVarExpressions(object.at(key), v);
            }
        }
    }
}

void UndefinedVariables(Stmt* program)
{
    std::stringstream buff;
    auto* old = std::cout.rdbuf(buff.rdbuf());

    auto astPrinter = AstPrinter();
    astPrinter.Print(program);

    std::cout.rdbuf(old);

    json object = json::parse(buff);

    vector<std::string> declarations;
    FindDeclarations(object, declarations);

    vector<std::string> varExpressions;
    FindVarExpressions(object, varExpressions);

    for (auto const& it : varExpressions) {
        if (std::find(declarations.begin(), declarations.end(), it) == declarations.end()) {
            std::cout << it << " not declared!" << std::endl;
        }
    }
}

void UnusedVariables(Stmt* program)
{
    std::stringstream buff;
    auto* old = std::cout.rdbuf(buff.rdbuf());

    auto astPrinter = AstPrinter();
    astPrinter.Print(program);

    std::cout.rdbuf(old);

    json object = json::parse(buff);

    vector<std::string> declarations;
    FindDeclarations(object, declarations);

    vector<std::string> varExpressions;
    FindVarExpressions(object, varExpressions);

    for (auto const& it : declarations) {
        if (std::find(varExpressions.begin(), varExpressions.end(), it) == varExpressions.end()) {
            std::cout << it << " not used!" << std::endl;
        }
    }
}
