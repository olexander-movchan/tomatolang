#include "symbols.hpp"
#include "errors.hpp"


using namespace Tomato;


Symbol::Symbol(const std::string &name) : name(name) {}


SymbolTable::SymbolTable(CodeNavigator &navigator) : navigator(navigator)
{
    // Create global scope
    symbols.emplace_back();
}


void SymbolTable::define(const Symbol &symbol)
{
    if (symbols.back().find(symbol.name) != symbols.back().end())
        throw NameError(navigator.top(), "Name '" + symbol.name + "' is redefined");

    symbols.back().insert({symbol.name, symbol});
}


Symbol SymbolTable::lookup(const std::string &name)
{
    for (auto scope = symbols.rbegin(); scope != symbols.rend(); ++scope)
    {
        if (scope->find(name) != scope->end())
            return scope->at(name);
    }

    throw NameError(navigator.top(), "Undefined name '" + name + "'");
}

void SymbolTable::push_scope()
{
    symbols.emplace_back();
}

void SymbolTable::pop_scope()
{
    symbols.pop_back();
}
