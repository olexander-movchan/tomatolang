#include "syntax_tree.hpp"


using namespace Tomato::Syntax;


Identifier::Identifier(const std::string &name) : name(name) {}

Literal::Literal(const std::string &lexeme) : lexeme(lexeme) {}

BinaryOperation::BinaryOperation(
        std::shared_ptr<Expression> left,
        BinaryOperator operation,
        std::shared_ptr<Expression> right)
        : left(left), operation(operation), right(right) {}


UnaryOperation::UnaryOperation(
        UnaryOperator operation,
        std::shared_ptr<Expression> operand)
        : operation(operation), operand(operand) {}


Indexation::Indexation(
        std::shared_ptr<Expression> array,
        std::shared_ptr<Expression> index)
        : array(array), index(index) {}


Call::Call(std::shared_ptr<Expression> function) : function(function) {}


MemberAccess::MemberAccess(
        std::shared_ptr<Expression> expression,
        std::shared_ptr<Identifier> member)
        : expression(expression), member(member) {}


StatementBlock::StatementBlock(std::vector<std::shared_ptr<Statement>> statements) : statements(statements) {}


ValueDeclaration::ValueDeclaration(
        std::shared_ptr<Identifier> variable,
        std::shared_ptr<Expression> value,
        bool constant)
        : variable(variable), value(value), constant(constant) {}


ConditionalStatement::ConditionalStatement(
        std::shared_ptr<Expression> condition,
        std::shared_ptr<StatementBlock> then_case,
        std::shared_ptr<StatementBlock> else_case)
        : condition(condition), then_case(then_case), else_case(else_case) {}


ConditionalLoop::ConditionalLoop(
        std::shared_ptr<Expression> condition,
        std::shared_ptr<StatementBlock> body)
        : condition(condition), body(body) {}


PrintStatement::PrintStatement(std::shared_ptr<Expression> expression) : expression(expression) {}

ReadStatement::ReadStatement(std::shared_ptr<Expression> expression) : expression(expression) {}
