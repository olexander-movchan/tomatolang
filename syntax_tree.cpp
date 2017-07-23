#include "syntax_tree.hpp"


// Abstract syntax tree children's constructors

AbstractSyntaxTree::AbstractSyntaxTree(const Token &token) : token(token) {}
Expression::Expression(const Token &token) : AbstractSyntaxTree(token) {}
IntegerConstant::IntegerConstant(const Token &token) : Expression(token) {}
BinaryOperator::BinaryOperator(const Token &token,
                               std::shared_ptr<Expression> left,
                               std::shared_ptr<Expression> right)
        : Expression(token), left(left), right(right) {}


// Accept visitor (look for 'visitor' pattern)

void IntegerConstant::accept(ASTVisitor &visitor)
{
    visitor.visit(*this);
}

void BinaryOperator::accept(ASTVisitor &visitor)
{
    visitor.visit(*this);
}


// General visit method of Visitor pattern

void ASTVisitor::visit(AbstractSyntaxTree &ast_node)
{
    ast_node.accept(*this);
}
