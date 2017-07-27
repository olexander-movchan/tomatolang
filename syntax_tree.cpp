#include "syntax_tree.hpp"


using namespace AST;


// AST node constructors


AbstractSyntaxTree::AbstractSyntaxTree(const Token &token) : token(token) {}


Program::Program      (const Token &token) : AbstractSyntaxTree(token) {}
Statement::Statement  (const Token &token) : AbstractSyntaxTree(token) {}
Expression::Expression(const Token &token) : AbstractSyntaxTree(token) {}


Constant::Constant(const Token &token) : Expression(token) {}
Variable::Variable(const Token &token) : Expression(token) {}


BinaryOperator::BinaryOperator(std::shared_ptr<Expression> left,
                               const Token &token,
                               std::shared_ptr<Expression> right)

        : Expression(token), left(left), right(right) {}


UnaryOperator::UnaryOperator(const Token &token,
                             std::shared_ptr<Expression> expr)

        : Expression(token), operand(expr) {}


Assignment::Assignment(std::shared_ptr<Variable> variable,
                       Token token,
                       std::shared_ptr<Expression> expression)

        : Statement(token), variable(variable), expression(expression) {}


// Visitor-related methods

void Visitor::visit(AbstractSyntaxTree &node) { node.accept(*this); }

void Program         ::accept(Visitor &visitor) { visitor.visit(*this); }
void UnaryOperator   ::accept(Visitor &visitor) { visitor.visit(*this); }
void BinaryOperator  ::accept(Visitor &visitor) { visitor.visit(*this); }
void Variable        ::accept(Visitor &visitor) { visitor.visit(*this); }
void Constant        ::accept(Visitor &visitor) { visitor.visit(*this); }
void Assignment      ::accept(Visitor &visitor) { visitor.visit(*this); }
