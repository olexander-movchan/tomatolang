#include "printer.hpp"


using namespace Tomato::Syntax;


Printer::Printer(std::ostream &stream) : stream(stream) {}


void Printer::print(ASTNode &tree)
{
    visit(tree);
}


void Printer::process(StatementBlock &node)
{
    for (auto &statement : node.statements)
    {
        visit(*statement);
        stream << std::endl;
    }
}

void Printer::process(Identifier &node)
{
    stream << "<ID: " << node.name << ">";
}

void Printer::process(Literal &node)
{
    stream << "<L: " << node.lexeme << ">";
}

void Printer::process(BinaryOperation &node)
{
    stream << "(";
    visit(*node.left);
    stream << " <OP> ";
    visit(*node.right);
    stream << ")";
}

void Printer::process(UnaryOperation &node)
{
    stream << "<OP> (";
    visit(*node.operand);
    stream << ")";
}

void Printer::process(Indexation &node)
{
    visit(*node.array);
    stream << "[";
    visit(*node.index);
    stream << "]";
}

void Printer::process(Call &node)
{
    visit(*node.function);
    stream << "()";
}

void Printer::process(MemberAccess &node)
{
    visit(*node.expression);
    stream << ".";
    visit(*node.member);
}

void Printer::process(ConditionalStatement &node)
{
    stream << "if ";
    visit(*node.condition);
    stream << " then\n";
    visit(*node.then_case);
    stream << "else\n";
    visit(*node.else_case);
    stream << "end ";
}

void Printer::process(ConditionalLoop &node)
{
    stream << "while ";
    visit(*node.condition);
    stream << " do\n";
    visit(*node.body);
    stream << "end";
}

void Printer::process(PrintStatement &node)
{
    stream << "print ";
    visit(*node.expression);
}

void Printer::process(ReadStatement &node)
{
    stream << "read ";
    visit(*node.expression);
}

void Printer::process(struct InvalidStatement &node)
{
    stream << "INVALID";
}
