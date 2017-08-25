#include "syntax_tree.hpp"


using namespace AST;


Expression::Expression(const Token &token) : token(token) {}


Literal::Literal(const Token &token) : Expression(token), lexeme(token.lexeme)
{
    if (lexeme == "true" || lexeme == "false")
        type = Type ::Bool;

    else if (lexeme.find('.') == lexeme.npos)
        type = Type::Integer;

    else
        type = Type::Float;
}


int   Literal::ivalue() { return std::stoi(lexeme); }
float Literal::fvalue() { return std::stof(lexeme); }
bool  Literal::bvalue() { return lexeme == "true"; }


Identifier::Identifier(const Token &token) : Expression(token), name(token.lexeme) {}


BinaryOperator::BinaryOperator(std::shared_ptr<Expression> left,
                               const Token &operator_t,
                               std::shared_ptr<Expression> right)
        : Expression(operator_t), left(left), operation(operator_t.type), right(right) {}


UnaryOperator::UnaryOperator(const Token &operator_t, std::shared_ptr<Expression> expression)
        : Expression(operator_t), operation(operator_t.type), expression(expression) {}


Assignment::Assignment(std::shared_ptr<Expression> lvalue,
                       const Token                 &set,
                       std::shared_ptr<Expression> rvalue)
        : token(set), lvalue(lvalue) , rvalue(rvalue) {}


Declaration::Declaration(const Token &var, std::shared_ptr<Identifier> variable,
                         const Token &set, std::shared_ptr<Expression> value)
        : token_var(var), token_set(set), variable(variable), value(value) {}


Conditional::Conditional(std::shared_ptr<Expression> condition,
                         std::shared_ptr<Statements> consequent,
                         std::shared_ptr<Statements> alternative)
        : condition(condition), consequent(consequent), alternative(alternative) {}


WhileLoop::WhileLoop(std::shared_ptr<Expression> condition,
                     std::shared_ptr<Statements> statements)
        : condition(condition), statements(statements) {}


Print::Print(std::shared_ptr<Expression> expression) : expression(expression) {}


// Visitor-related methods

void Visitor::visit(AbstractSyntaxTree &node) { node.accept(*this); }

void Statements      ::accept(Visitor &visitor) { visitor.visit(*this); }

void Print           ::accept(Visitor &visitor) { visitor.visit(*this); }
void Assignment      ::accept(Visitor &visitor) { visitor.visit(*this); }
void Declaration     ::accept(Visitor &visitor) { visitor.visit(*this); }

void BinaryOperator  ::accept(Visitor &visitor) { visitor.visit(*this); }
void UnaryOperator   ::accept(Visitor &visitor) { visitor.visit(*this); }
void Identifier      ::accept(Visitor &visitor) { visitor.visit(*this); }
void Literal         ::accept(Visitor &visitor) { visitor.visit(*this); }

void Conditional     ::accept(Visitor &visitor) { visitor.visit(*this); }
void WhileLoop       ::accept(Visitor &visitor) { visitor.visit(*this); }
