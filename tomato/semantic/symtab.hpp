#ifndef TOMATO_SYMBOL_TABLE_HPP
#define TOMATO_SYMBOL_TABLE_HPP


#include <string>
#include <memory>
#include <map>
#include <vector>

#include "symbols.hpp"
#include "operators.hpp"


namespace Tomato::Semantic
{
    class SymbolTable
    {
    public:
        SymbolTable();

        template <typename T>
        void define_symbol(const std::string &name, const T &symbol);

        template <typename T>
        T lookup_symbol(const std::string &name);

        void push_scope();
        void pop_scope();

    private:
        using Scope = std::map<std::string, std::shared_ptr<Symbol>>;

        std::vector<Scope> symbols;
    };
}


#endif //TOMATO_SYMBOL_TABLE_HPP
