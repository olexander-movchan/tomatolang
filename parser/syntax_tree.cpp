#include "syntax_tree.hpp"


using namespace AST;


// AST node constructors
Assignment::Assignment(std::shared_ptr<Expression> lvalue,
                       std::shared_ptr<Expression> rvalue)

        : lvalue(lvalue), rvalue(rvalue) {}


Declaration::Declaration(std::shared_ptr<Identifier> variable,
                         std::shared_ptr<Expression> value)

        : variable(variable), value(value) {}


Literal::Literal(const std::string &lexeme) : lexeme(lexeme)
{
    if (lexeme.find('.') == lexeme.npos)
        type = Type::Integer;
    else
        type = Type::Float;
}


BinaryOperator::BinaryOperator(std::shared_ptr<Expression> left,
                               Token::Type                 operation,
                               std::shared_ptr<Expression> right)

        : left(left), operation(operation), right(right) {}


UnaryOperator::UnaryOperator(Token::Type                 operation,
                             std::shared_ptr<Expression> expression)

        : operation(operation), expression(expression) {}


Identifier::Identifier(const std::string &name) : name(name) {}


int   Literal::ivalue() { return std::stoi(lexeme); }
float Literal::fvalue() { return std::stof(lexeme); }


// Visitor-related methods

void Visitor::visit(AbstractSyntaxTree &node) { node.accept(*this); }

void Program         ::accept(Visitor &visitor) { visitor.visit(*this); }
void UnaryOperator   ::accept(Visitor &visitor) { visitor.visit(*this); }
void BinaryOperator  ::accept(Visitor &visitor) { visitor.visit(*this); }
void Identifier      ::accept(Visitor &visitor) { visitor.visit(*this); }
void Literal         ::accept(Visitor &visitor) { visitor.visit(*this); }
void Assignment      ::accept(Visitor &visitor) { visitor.visit(*this); }
void Declaration     ::accept(Visitor &visitor) { visitor.visit(*this); }
