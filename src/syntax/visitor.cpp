#include "visitor.hpp"
#include "syntax_tree.hpp"



using namespace Tomato;
using namespace Tomato::AST;


void Visitor::visit(AbstractNode &node)
{
    navigator.push(node.location);

    node.accept(*this);

    navigator.pop();
}
