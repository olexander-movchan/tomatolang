#include "interpreter.hpp"

#include <iostream>
#include <iomanip>

#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "syntax/printer.hpp"


using namespace Tomato;


Interpreter::Interpreter(std::istream &istream, std::ostream &ostream) : istream(istream), ostream(ostream)
{
    symbol_int = symtab.define("int");
    symbol_float = symtab.define("float");
    symbol_bool = symtab.define("bool");

    types = {symbol_int, symbol_float, symbol_bool};

    operations.init_builtins(symbol_int, symbol_float, symbol_bool);
}


void Interpreter::run()
{
    Syntax::Parser parser;

    char const * const prompt = ">>> ";

    while (true)
    {
        char * line = readline(prompt);

        if (line == nullptr) // EOF reached
        {
            ostream << std::endl;
            break;
        }
        else if (line[0] == '\0') // Line is empty
        {
            continue;
        }

        // save readline history
        add_history(line);

        parser.set_text(line);
        free(line);

        try
        {
            auto tree = parser.parse();
            visit(*tree);
        }
        catch (Syntax::SyntaxError &error)
        {
            std::cout << "syntax error: " << error.what() << std::endl;
        }
        catch (Semantic::SemanticError &error)
        {
            std::cout << "semantic error: " << error.what() << std::endl;
        }
    }
}


void Interpreter::process(Syntax::Program &node)
{
    throw std::runtime_error("this feature is not implemented");
}

void Interpreter::process(Syntax::ValueDeclaration &node)
{
    auto var_sym = symtab.define(node.value->name);

    if (node.init)
    {
        visit(*node.init);

        if (node.type)
        {
            auto type_sym = symtab.lookup(node.type->name);

            if (types.find(type_sym) == types.end())
            {
                throw Semantic::SemanticError(node.type->name + " does not name a type");
            }

            if (type_sym != temp->type)
            {
                throw Semantic::SemanticError("specified type doesn't match initializer");
            }
        }

        memory[var_sym] = std::move(temp);
    }
    else if (node.type)
    {
        auto type_sym = symtab.lookup(node.type->name);

        if (types.find(type_sym) == types.end())
        {
            throw Semantic::SemanticError(node.type->name + " does not name a type");
        }

        try
        {
            if (type_sym == symbol_int)
                memory[var_sym] = std::make_shared<Runtime::Scalar<int>>(symbol_int, 0);
            else if (type_sym == symbol_float)
                memory[var_sym] = std::make_shared<Runtime::Scalar<float>>(symbol_float, 0.0f);
            else if (type_sym == symbol_bool)
                memory[var_sym] = std::make_shared<Runtime::Scalar<bool>>(symbol_bool, false);
            else
                throw Semantic::SemanticError("undefined type");
        }
        catch (std::out_of_range &)
        {
            throw Semantic::SemanticError(node.type->name + " doesn't name a type");
        }
    }
    else
    {
        throw std::logic_error("value declaration should contain type specification or initializer");
    }
}

void Interpreter::process(Syntax::Identifier &node)
{
    auto var_sym = symtab.lookup(node.name);

    try
    {
        temp = memory.at(var_sym);
    }
    catch (std::out_of_range &)
    {
        throw Semantic::SemanticError(node.name + " does not name an object");
    }
}

void Interpreter::process(Syntax::Literal &node)
{
    temp = std::make_shared<Runtime::Scalar<int>>(symbol_int, std::stoi(node.lexeme));
}

void Interpreter::process(Syntax::BinaryOperation &node)
{
    visit(*node.left);
    auto left = temp;

    visit(*node.right);
    auto right = temp;

    temp = operations.lookup(left->type, node.operation, right->type)(*left, *right);
}

void Interpreter::process(Syntax::UnaryOperation &node)
{
    visit(*node.operand);

    temp = operations.lookup(node.operation, temp->type)(*temp);
}

void Interpreter::process(Syntax::ConditionalStatement &node)
{
    visit(*node.condition);

    bool cond;

    try
    {
        cond = dynamic_cast<Runtime::Scalar<bool>&>(*temp).value;
    }
    catch (std::bad_cast &)
    {
        throw Semantic::SemanticError("condition must be bool");
    }

    if (cond)
        visit(*node.then_case);
    else
        visit(*node.else_case);
}

void Interpreter::process(Syntax::ConditionalLoop &node)
{
    bool cond;

    while (true)
    {
        visit(*node.condition);

        try
        {
            cond = dynamic_cast<Runtime::Scalar<bool> &>(*temp).value;
        }
        catch (std::bad_cast &)
        {
            throw Semantic::SemanticError("condition must be bool");
        }

        if (cond)
            visit(*node.body);
        else
            break;
    }
}

void Interpreter::process(Syntax::PrintStatement &node)
{
    visit(*node.expression);

    try
    {
        if (temp->type == symbol_int)
            ostream << dynamic_cast<Runtime::Scalar<int> &>(*temp).value << std::endl;
        else if (temp->type == symbol_float)
            ostream << dynamic_cast<Runtime::Scalar<float> &>(*temp).value << std::endl;
        else if (temp->type == symbol_bool)
            ostream << std::boolalpha << dynamic_cast<Runtime::Scalar<bool> &>(*temp).value << std::endl;
    }
    catch (std::bad_cast &)
    {
        throw std::logic_error("internal interpretation error");
    }
}

void Interpreter::process(Syntax::ReadStatement &node)
{
    visit(*node.expression);

    try
    {
        if (temp->type == symbol_int)
            istream >> dynamic_cast<Runtime::Scalar<int> &>(*temp).value;
        else if (temp->type == symbol_float)
            istream >> dynamic_cast<Runtime::Scalar<float> &>(*temp).value;
        else if (temp->type == symbol_bool)
            istream >> dynamic_cast<Runtime::Scalar<bool> &>(*temp).value;
    }
    catch (std::bad_cast &)
    {
        throw std::logic_error("internal interpretation error");
    }
}

void Interpreter::process(Syntax::StatementBlock &node)
{
    symtab.push_scope();

    for (auto &statement : node.statements)
    {
        visit(*statement);
    }

    symtab.pop_scope();
}
