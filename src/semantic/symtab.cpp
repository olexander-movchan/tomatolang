#include "symtab.hpp"


using namespace Tomato::Semantic;


Symbol SymbolTable::NextSymbol = 0;


SymbolTable::SymbolTable()
{
    push_scope();
}


void SymbolTable::push_scope()
{
    symbols.emplace_back();
}


void SymbolTable::pop_scope()
{
    symbols.pop_back();
}


const SymbolTable::Scope &SymbolTable::scope()
{
    return symbols.back();
}


Symbol SymbolTable::define(const std::string &name)
{
    if (symbols.back().find(name) != symbols.back().end())
    {
        throw SemanticError("name '" + name + "' is already defined at this scope");
    }

    symbols.back()[name] = NextSymbol++;

    return NextSymbol - 1;
}


Symbol SymbolTable::lookup(const std::string &name)
{
    for (auto scope = symbols.rbegin(); scope != symbols.rend(); ++scope)
    {
        try
        {
            return scope->at(name);
        }
        catch (std::out_of_range &) {}
    }

    throw SemanticError("undefined reference to '" + name + "'");
}
