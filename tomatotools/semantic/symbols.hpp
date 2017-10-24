#ifndef TOMATO_SYMBOLS_HPP
#define TOMATO_SYMBOLS_HPP


#include <unordered_map>
#include <vector>
#include <errors.hpp>
#include "syntax/navigator.hpp"


namespace Tomato
{
    /**
     * @brief Symbol is a named piece of data
     */
    class Symbol
    {
    public:
        explicit Symbol(const std::string &name);

        std::string name;
    };


    /**
     * @brief SymbolTable stores symbols, controls their definition and lookup.
     */
    class SymbolTable
    {
    public:
        /**
         * @param navigator syntax tree navigator is used for error reporting
         */
        explicit SymbolTable(CodeNavigator & navigator);

        /**
         * @brief Defines new symbol
         * @param symbol symbol that should be defined
         * @throw NameError is thrown if symbol with such name is already defined
         */
        void define(const Symbol &symbol);

        /**
         * @brief Look up for a symbol with specified name
         * @param name symbol name
         * @return symbol requested symbol
         * @throw NameError is thrown if symobl with such name was not defined
         */
        Symbol lookup(const std::string &name);

        /**
         * @brief Creates new 'inner' scope where new declarations hide names from 'outer' scopes
         */
        void push_scope();

        /**
         * @brief Removes the most inner scope and all its names.
         */
        void pop_scope();

    private:
        CodeNavigator &navigator;
        using Scope = std::unordered_map<std::string, Symbol>;

        std::vector<Scope> symbols;
    };
}


#endif //TOMATO_SYMBOLS_HPP
