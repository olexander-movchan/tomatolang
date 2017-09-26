#include "parser.hpp"
#include "errors.hpp"


using namespace Tomato;


const int MaxPrecedence = 5;


int precedence(Token::Type op)
{
    switch (op)
    {
        case Token::Type::Or:
            return 0;

        case Token::Type::And:
            return 1;

        case Token::Type::LT:
        case Token::Type::GT:
        case Token::Type::LE:
        case Token::Type::GE:
        case Token::Type::EQ:
        case Token::Type::NE:
            return 2;

        case Token::Type::Add:
        case Token::Type::Sub:
            return 3;

        case Token::Type::Mul:
        case Token::Type::Div:
            return 4;

        case Token::Type::Exp:
            return 5;

        default:
            return -1;
    }
}


bool left_associative(Token::Type op)
{
    switch (op)
    {
        case Token::Type::Exp:
            return false;

        default:
            return true;
    }
}


void Parser::shift()
{
    current_token = lexer.next_token();
    navigator.move(current_token.location);
}


void Parser::shift(Token::Type expected_type)
{
    if (current_token.type == expected_type)
    {
        shift();
    }
    else
    {
        throw SyntaxError(navigator.top(), "Unexpected token");
    }
}


std::shared_ptr<AST::AbstractNode> Parser::parse(const std::string &code)
{
    lexer.reset(code);
    shift();

    return statement_list();
}


std::shared_ptr<AST::ExpressionNode> Parser::expression(const std::string &code)
{
    lexer.reset(code);
    shift();

    return expression();
}


std::shared_ptr<AST::ExpressionNode> Parser::expression(int curr_precedence)
{
    if (curr_precedence > MaxPrecedence)
        return term();

    auto expr = expression(curr_precedence + 1);

    if (!current_token.is_binary_op() || precedence(current_token.type) > curr_precedence)
        return expr;

    if (left_associative(current_token.type))
    {
        while (precedence(current_token.type) == curr_precedence)
        {
            auto op = current_token;
            shift();

            expr = std::make_shared<AST::BinaryOperatorNode>(
                    expr,
                    op,
                    expression(curr_precedence + 1)
            );
        }
    }
    else
    {
        auto op = current_token;
        shift();

        expr = std::make_shared<AST::BinaryOperatorNode>(
                expr,
                op,
                expression(curr_precedence)
        );
    }

    return expr;
}


std::shared_ptr<AST::ExpressionNode> Parser::term()
{
    switch (current_token.type)
    {
        case Token::Type::LParen:
        {
            shift(Token::Type::LParen);
            auto expr = expression();
            shift(Token::Type::RParen);

            return expr;
        }

        case Token::Type::Not:
        case Token::Type::Add:
        case Token::Type::Sub:
        {
            auto un_op = current_token;

            shift();

            // Read only product:
            // TODO: Remove hardcoded value
            auto expr = expression(4);

            return std::make_shared<AST::UnaryOperatorNode>(un_op, expr);
        }

        case Token::Type::Identifier:
        {
            auto identifier = std::make_shared<AST::IdentifierNode>(current_token);
            shift();
            return identifier;
        }

        case Token::Type::Literal:
        {
            auto literal = std::make_shared<AST::LiteralNode>(current_token);
            shift();
            return literal;
        }

        default:
            throw SyntaxError(navigator.top(), "Unexpected token");
    }
}


std::shared_ptr<AST::StatementNode> Parser::statement()
{
    switch (current_token.type)
    {
        case Token::Type::Print:
            return print();

        case Token::Type::Var:
            return declaration();

        case Token::Type::If:
            return conditional();

        case Token::Type::While:
            return while_loop();

        // Expression begins with on of next tokens:
        case Token::Type::LParen:
        case Token::Type::Add:
        case Token::Type::Sub:
        case Token::Type::Not:
        case Token::Type::Literal:
        case Token::Type::Identifier:
        {
            auto expr = expression();

            if (current_token.type == Token::Type::Assign)
            {
                auto location = current_token.location;
                shift();

                auto source = expression();

                return std::make_shared<AST::AssignmentNode>(location, expr, source);
            }

            return expr;
        }

        default:
            throw SyntaxError(navigator.top(), "Unexpected token");
    }
}


std::shared_ptr<AST::DeclarationNode> Parser::declaration()
{
    auto token_var = current_token;
    shift(Token::Type::Var);

    auto var = std::make_shared<AST::IdentifierNode>(current_token);
    shift(Token::Type::Identifier);

    auto token_set = current_token;
    shift(Token::Type::Assign);

    auto expr = expression();

    return std::make_shared<AST::DeclarationNode>(token_var.location, var, expr);
}


std::shared_ptr<AST::ConditionalNode> Parser::conditional()
{
    auto location = current_token.location;

    shift(Token::Type::If);

    auto condition = expression();

    shift(Token::Type::Then);

    auto consequent = statement_list();

    decltype(statement_list()) alternative;

    if (current_token.type == Token::Type::Else)
    {
        shift(Token::Type::Else);
        alternative = statement_list();
    }

    shift(Token::Type::End);

    return std::make_shared<AST::ConditionalNode>(location, condition, consequent, alternative);
}


std::shared_ptr<AST::LoopNode> Parser::while_loop()
{
    auto location = current_token.location;

    shift(Token::Type::While);
    auto condition = expression();

    shift(Token::Type::Do);
    auto body = statement_list();
    shift(Token::Type::End);

    return std::make_shared<AST::LoopNode>(location, condition, body);
}


std::shared_ptr<AST::PrintNode> Parser::print()
{
    auto location = current_token.location;

    shift(Token::Type::Print);
    auto expr = expression();

    return std::make_shared<AST::PrintNode>(location, expr);
}


std::shared_ptr<AST::StatementListNode> Parser::statement_list()
{
    auto st = std::make_shared<AST::StatementListNode>(navigator.top());

    while (current_token.type != Token::Type::EndOfFile &&
           current_token.type != Token::Type::Else &&
           current_token.type != Token::Type::End)
    {
        st->statements.push_back(statement());
    }

    return st;
}
