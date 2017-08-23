#include "parser.hpp"
#include "errors.hpp"


using namespace AST;


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
            throw std::runtime_error("Getting precedence of non-operator");
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


void Parser::shift(Token::Type expected_type)
{
    if (current_token.type == expected_type)
    {
        current_token = lexer->next();
    }
    else
    {
        throw SyntaxError(current_token, "Unexpected token: " + current_token.lexeme);
    }
}


std::shared_ptr<Program> Parser::parse(const std::string &code)
{
    lexer = std::make_unique<Lexer>(code);
    current_token = lexer->next();

    auto program = std::make_shared<Program>();

    while (current_token.type != Token::Type::EndOfFile)
    {
        program->statements.push_back(statement());
    }

    lexer = nullptr;

    return program;
}


std::shared_ptr<Expression> Parser::expression(int curr_precedence)
{
    if (curr_precedence > MaxPrecedence)
        return term();

    auto expr = expression(curr_precedence + 1);
  
    if (current_token.is_binary_op() && left_associative(current_token.type))
    {
        while (current_token.is_binary_op() && precedence(current_token.type) == curr_precedence)
        {
            auto bin_op = current_token;
            shift(current_token.type);

            expr = std::make_shared<BinaryOperator>(expr,
                                                    bin_op,
                                                    expression(curr_precedence + 1));
        }
    }
    else if (current_token.is_binary_op())
    {
        if (current_token.is_binary_op() && precedence(current_token.type) == curr_precedence)
        {
            auto bin_op = current_token;
            shift(current_token.type);

            expr = std::make_shared<BinaryOperator>(expr,
                                                    bin_op,
                                                    expression(curr_precedence));

        }
    }

    return expr;
}


std::shared_ptr<Expression> Parser::term()
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

            shift(current_token.type);

            // Read only product:
            // TODO: Remove hardcoded value
            auto expr = expression(4);

            return std::make_shared<UnaryOperator>(un_op, expr);
        }

        case Token::Type::Identifier:
        {
            auto identifier = std::make_shared<Identifier>(current_token);
            shift(current_token.type);
            return identifier;
        }

        case Token::Type::Literal:
        {
            auto literal = std::make_shared<Literal>(current_token);
            shift(current_token.type);
            return literal;
        }

        default:
            throw SyntaxError(current_token, "Unexpected token");
    }
}


std::shared_ptr<Statement> Parser::statement()
{
    if (current_token.type == Token::Type::Var)
        return declaration();

    auto expr = expression();

    if (current_token.type == Token::Type::Assign)
    {
        auto token = current_token;
        shift(Token::Type::Assign);

        auto rvalue = expression();

        return std::make_shared<Assignment>(expr, token, rvalue);
    }

    return expr;
}


std::shared_ptr<Statement> Parser::declaration()
{
    auto token_var = current_token;
    shift(Token::Type::Var);

    auto var = std::make_shared<Identifier>(current_token);
    shift(Token::Type::Identifier);

    auto token_set = current_token;
    shift(Token::Type::Assign);

    auto expr = expression();

    return std::make_shared<Declaration>(token_var, var, token_set, expr);
}
