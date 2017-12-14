#include "symtab.hpp"


using namespace Tomato::Semantic;


SymbolTable::SymbolTable()
{

}


template<typename T>
void SymbolTable::define_symbol(const std::string &name, const T &symbol)
{
    symbols.back().insert(name, std::make_shared<Symbol>(symbol));
}


template<typename T>
T SymbolTable::lookup_symbol(const std::string &name)
{
    for (auto scope = symbols.rbegin(); scope != symbols.rend(); scope++)
    {
        try
        {
            return dynamic_cast<T>(scope->at(name));
        }
        catch (std::out_of_range &) {}
        catch (std::bad_cast &) {}
    }
}
