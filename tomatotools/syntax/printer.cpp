#include "printer.hpp"


using namespace Tomato;
using namespace Tomato::AST;


std::string Printer::print(AbstractNode &tree)
{
    buffer.str(""); // set buffer empty

    Visitor::visit(tree);

    return buffer.str();
}


void Printer::print_indent()
{
    for (int i = 0; i < indent; ++i)
    {
        buffer << "    ";
    }
}


void Printer::visit(StatementListNode &node)
{
    for (auto &statement : node.statements)
    {
        Visitor::visit(*statement);
    }
}


void Printer::visit(PrintNode &node)
{
    print_indent();
    buffer << "Print" << std::endl;

    indent += 1;
    Visitor::visit(*node.expression);
    indent -= 1;
}


void Printer::visit(AssignmentNode &node)
{
    print_indent();
    buffer << "Assignment" << std::endl;

    indent += 1;
    Visitor::visit(*node.lvalue);

    print_indent();
    buffer << ":=" << std::endl;

    Visitor::visit(*node.rvalue);
    indent -= 1;
}


void Printer::visit(DeclarationNode &node)
{
    print_indent();
    buffer << "Declaration {" << node.variable->name << '}' << std::endl;

    indent += 1;
    Visitor::visit(*node.value);
    indent -= 1;
}


void Printer::visit(BinaryOperatorNode &node)
{
    print_indent();
    buffer << node.token.lexeme << std::endl;

    indent += 1;
    Visitor::visit(*node.left);
    Visitor::visit(*node.right);
    indent -= 1;
}


void Printer::visit(UnaryOperatorNode &node)
{
    print_indent();
    buffer << node.token.lexeme<< std::endl;

    indent += 1;
    Visitor::visit(*node.expression);
    indent -= 1;

}


void Printer::visit(IdentifierNode &node)
{
    print_indent();
    buffer << "Identifier {" << node.name << '}' << std::endl;
}


void Printer::visit(LiteralNode &node)
{
    print_indent();
    buffer << node.lexeme << std::endl;
}


void Printer::visit(ConditionalNode &node)
{
    print_indent();
    buffer << "if" << std::endl;

    indent += 1;
    Visitor::visit(*node.condition);
    indent -= 1;

    print_indent();
    buffer << "then" << std::endl;

    indent += 1;
    visit(*node.consequent);
    indent -= 1;

    print_indent();
    buffer << "else" << std::endl;

    indent += 1;
    visit(*node.alternative);
    indent -= 1;

    print_indent();
    buffer << "end" << std::endl;
}


void Printer::visit(LoopNode &node)
{
    print_indent();
    buffer << "while" << std::endl;

    indent += 1;
    Visitor::visit(*node.condition);
    indent -= 1;

    print_indent();
    buffer << "then" << std::endl;

    indent += 1;
    visit(*node.statements);
    indent -= 1;

    print_indent();
    buffer << "end" << std::endl;
}
