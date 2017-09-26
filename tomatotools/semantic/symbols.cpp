#include "symbols.hpp"
#include "errors.hpp"


using namespace Tomato;


Symbol::Symbol(const std::string &name) : name(name) {}


SymbolTable::SymbolTable(CodeNavigator &navigator) : navigator(navigator) {}


void SymbolTable::define(const Symbol &symbol)
{
    if (symbols.find(symbol.name) != symbols.end())
        throw NameError(navigator.top(), "Name '" + symbol.name + "' is redefined");

    symbols.insert({symbol.name, symbol});
}

Symbol SymbolTable::lookup(const std::string &name)
{
    if (symbols.find(name) == symbols.end())
        throw NameError(navigator.top(), "Undefined name '" + name + "'");

    return symbols.find(name)->second;
}
