#ifndef TOMATO_SYMBOL_TABLE_HPP
#define TOMATO_SYMBOL_TABLE_HPP


#include <string>
#include <vector>
#include <map>
#include <memory>


namespace Tomato::Semantic
{
    using Symbol = size_t;


    class SemanticError : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };


    class SymbolTable
    {
    public:
        SymbolTable();

        Symbol define(const std::string &name);
        Symbol lookup(const std::string &name);

        using Scope = std::map<std::string, Symbol>;

        void push_scope();
        void pop_scope();

        const Scope & scope();

    private:
        std::vector<Scope> symbols;

        static Symbol NextSymbol;
    };
}


#endif //TOMATO_SYMBOL_TABLE_HPP
