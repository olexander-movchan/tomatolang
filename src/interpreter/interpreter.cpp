#include "interpreter.hpp"

#include <iostream>
#include <iomanip>

#include <readline/readline.h>
#include <readline/history.h>

#include "syntax/parser.hpp"
#include "syntax/printer.hpp"


using namespace Tomato;


struct FunctionReturn
{
    std::shared_ptr<Runtime::Object> object;
};


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

    const char * const primary_prompt = ">>> ";
    const char * const append_prompt = "... ";

    const char * prompt = primary_prompt;

    std::string statement;

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

        using namespace std::string_literals;
        statement += " "s + line;
        add_history(line);
        free(line);

        parser.set_text(statement);

        try
        {
            auto tree = parser.parse();
            visit(*tree);
        }
        catch (Syntax::SyntaxError &error)
        {
            if (parser.eof()) // unexpected EOF, try read more lines
            {
                prompt = append_prompt;
                continue;
            }

            std::cout << "syntax error: " << error.what() << std::endl;
        }
        catch (Semantic::SemanticError &error)
        {
            std::cout << "semantic error: " << error.what() << std::endl;
        }

        prompt = primary_prompt;
        statement.clear();
    }
}


void Interpreter::interpret(std::istream &file)
{
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    Syntax::Parser parser;
    parser.set_text(code);

    while (!parser.eof())
    {
        try
        {
            auto tree = parser.parse();
            visit(*tree);
        }
        catch (Syntax::SyntaxError &error)
        {
            std::cout << "syntax error: " << error.what() << std::endl;
            break;
        }
        catch (Semantic::SemanticError &error)
        {
            std::cout << "semantic error: " << error.what() << std::endl;
            break;
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

        memory[var_sym] = temp->clone();
        memory[var_sym]->is_mutable = !node.constant;
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
                memory[var_sym] = std::make_shared<Runtime::Scalar<int>>(symbol_int, 0, !node.constant);
            else if (type_sym == symbol_float)
                memory[var_sym] = std::make_shared<Runtime::Scalar<float>>(symbol_float, 0.0f, !node.constant);
            else if (type_sym == symbol_bool)
                memory[var_sym] = std::make_shared<Runtime::Scalar<bool>>(symbol_bool, false, !node.constant);
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

void Interpreter::process(Syntax::Assignment &node)
{
    visit(*node.source);
    auto source = temp;

    visit(*node.destination);
    auto destination = temp;

    temp.reset();

    if (destination.use_count() == 1)
    {
        throw Semantic::SemanticError("assigning to rvalue expression");
    }

    destination->assign(*source);
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
    switch (node.type)
    {
        case Syntax::Literal::Type::Integer:
            temp = std::make_shared<Runtime::Scalar<int>>(symbol_int, std::stoi(node.lexeme), false);
            break;

        case Syntax::Literal::Type::Float:
            temp = std::make_shared<Runtime::Scalar<float>>(symbol_float, std::stof(node.lexeme), false);
            break;

        case Syntax::Literal::Type::Boolean:
            temp = std::make_shared<Runtime::Scalar<bool>>(symbol_bool, node.lexeme == "true", false);
            break;

        default:
            throw std::logic_error("unsupported type");
    }
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
    else if (node.else_case)
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

void Interpreter::process(Syntax::Function &node)
{
    auto symbol = symtab.define(node.identifier->name);

    functions[symbol] = std::make_shared<Syntax::Function>(node);
}

void Interpreter::process(Syntax::Call &node)
{
    auto func_sym = symtab.lookup(node.function->name);

    if (functions.find(func_sym) == functions.end())
        throw Semantic::SemanticError(node.function->name + " does not name a function");

    auto func = functions[func_sym];

    if (node.arguments.size() != func->arguments.size())
        throw Semantic::SemanticError(
                "function " + func->identifier->name + " takes "
                + std::to_string(func->arguments.size()) + " arguments, but "
                + std::to_string(node.arguments.size()) + " provided");

    symtab.push_scope();

    for (int i = 0; i < node.arguments.size(); ++i)
    {
        auto expected_type_sym = symtab.lookup(func->arguments[i].type->name);

        visit(*node.arguments[i]);

        if (temp->type != expected_type_sym)
        {
            symtab.pop_scope();
            throw Semantic::SemanticError("parameter type mismatch");
        }

        auto param_sym = symtab.define(func->arguments[i].param->name);

        memory[param_sym] = temp->clone();
        memory[param_sym]->is_mutable = true;
    }

    try
    {
        visit(*func->body);

        if (func->return_type)
            throw Semantic::SemanticError("function did not return anything");

        temp = std::make_shared<Runtime::Scalar<bool>>(symbol_bool, true, false);
    }
    catch (FunctionReturn &ret)
    {
        if (!func->return_type)
            throw Semantic::SemanticError("function tries to return something");

        auto ret_sym = symtab.lookup(func->return_type->name);

        if (ret.object->type != ret_sym)
            throw Semantic::SemanticError("function's return type mismatch");

        temp = ret.object;
    }

    symtab.pop_scope();
}

void Interpreter::process(Syntax::ReturnStatement &node)
{
    visit(*node.expression);

    throw FunctionReturn {temp};
}
