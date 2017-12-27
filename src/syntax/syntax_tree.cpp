#include "syntax_tree.hpp"


using namespace Tomato::Syntax;


Identifier::Identifier(const std::string &name) : name(name) {}

Literal::Literal(Type type, const std::string &lexeme) : type(type), lexeme(lexeme) {}

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


MemberAccess::MemberAccess(
        std::shared_ptr<Expression> expression,
        std::shared_ptr<Identifier> member)
        : expression(expression), member(member) {}


StatementBlock::StatementBlock(std::vector<std::shared_ptr<Statement>> statements) : statements(statements) {}


ValueDeclaration::ValueDeclaration(
        std::shared_ptr<Identifier> value,
        std::shared_ptr<Identifier> type,
        std::shared_ptr<Expression> init,
        bool constant)
        : value(value), type(type), init(init), constant(constant) {}


ConditionalStatement::ConditionalStatement(
        std::shared_ptr<Expression> condition,
        std::shared_ptr<StatementBlock> then_case,
        std::shared_ptr<StatementBlock> else_case)
        : condition(condition), then_case(then_case), else_case(else_case) {}


ConditionalLoop::ConditionalLoop(
        std::shared_ptr<Expression> condition,
        std::shared_ptr<StatementBlock> body)
        : condition(condition), body(body) {}


Assignment::Assignment(
        std::shared_ptr<Expression> destination,
        std::shared_ptr<Expression> source)
        : destination(destination), source(source) {}


PrintStatement::PrintStatement(std::shared_ptr<Expression> expression) : expression(expression) {}


ReadStatement::ReadStatement(std::shared_ptr<Expression> expression) : expression(expression) {}

Function::Function(
        std::shared_ptr<Identifier> identifier,
        const std::vector<Function::Argument> &arguments,
        std::shared_ptr<Identifier> return_type,
        std::shared_ptr<StatementBlock> body)
        : identifier(identifier), arguments(arguments), return_type(return_type), body(body) {}

ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expression) : expression(expression) {}

Call::Call(
        std::shared_ptr<Identifier> function,
        const std::vector<std::shared_ptr<Expression>> &arguments)
        : function(function), arguments(arguments) {}
