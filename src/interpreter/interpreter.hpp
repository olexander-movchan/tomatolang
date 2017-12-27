#ifndef TOMATO_INTERPRETER_HPP
#define TOMATO_INTERPRETER_HPP


#include <ios>
#include <set>
#include "syntax/visitor.hpp"

#include "object.hpp"
#include "syntax/syntax_tree.hpp"
#include "semantic/symtab.hpp"
#include "operations.hpp"


namespace Tomato
{
    class Interpreter : private Syntax::Visitor
    {
    public:
        Interpreter(std::istream &istream, std::ostream &ostream);

        void run();

    private:
        void process(Syntax::Program               &node) override;
        void process(Syntax::ValueDeclaration      &node) override;
        void process(Syntax::Assignment            &node) override;
        void process(Syntax::Identifier            &node) override;
        void process(Syntax::Literal               &node) override;
        void process(Syntax::BinaryOperation       &node) override;
        void process(Syntax::UnaryOperation        &node) override;
        void process(Syntax::ConditionalStatement  &node) override;
        void process(Syntax::ConditionalLoop       &node) override;
        void process(Syntax::PrintStatement        &node) override;
        void process(Syntax::ReadStatement         &node) override;
        void process(Syntax::StatementBlock        &node) override;

    private:
        std::istream &istream;
        std::ostream &ostream;

        Semantic::Symbol symbol_int;
        Semantic::Symbol symbol_float;
        Semantic::Symbol symbol_bool;

        Semantic::SymbolTable symtab;
        std::shared_ptr<Runtime::Object> temp;

        Runtime::Operations operations;

        std::set<Semantic::Symbol> types;
        std::map<Semantic::Symbol, std::shared_ptr<Runtime::Object>> memory;
    };
}


#endif //TOMATO_INTERPRETER_HPP
