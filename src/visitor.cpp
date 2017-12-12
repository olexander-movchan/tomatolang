#include "visitor.hpp"
#include "syntax_tree.hpp"


using namespace Tomato::Syntax;


void Visitor::visit(ASTNode &node)
{
    node.accept(*this);
}
