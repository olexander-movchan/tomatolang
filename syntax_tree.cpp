#include "syntax_tree.hpp"


// Abstract syntax tree children's constructors

AbstractSyntaxTree::AbstractSyntaxTree(const Token &token) : token(token) {}
Expression::Expression(const Token &token) : AbstractSyntaxTree(token) {}
IntegerConstant::IntegerConstant(const Token &token) : Expression(token) {}

BinaryOperator::BinaryOperator(std::shared_ptr<Expression> left,
                               const Token &token,
                               std::shared_ptr<Expression> right)
        : Expression(token), left(left), right(right) {}

UnaryOperator::UnaryOperator(const Token &token,
                             std::shared_ptr<Expression> expr)
        : Expression(token), operand(expr) {}


// Accept visitor (look for 'visitor' pattern)

void IntegerConstant::accept(ASTVisitor &visitor)
{
    visitor.visit(*this);
}

void BinaryOperator::accept(ASTVisitor &visitor)
{
    visitor.visit(*this);
}

void UnaryOperator::accept(ASTVisitor &visitor)
{
    visitor.visit(*this);
}

void ASTVisitor::visit(AbstractSyntaxTree &ast_node)
{
    ast_node.accept(*this);
}
