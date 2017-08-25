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


std::shared_ptr<Statements> Parser::parse(const std::string &code)
{
    lexer = std::make_unique<Lexer>(code);
    current_token = lexer->next();

    auto program = statements();

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
                auto token = current_token;
                shift(Token::Type::Assign);

                auto rvalue = expression();

                return std::make_shared<Assignment>(expr, token, rvalue);
            }

            return expr;
        }

        default:
            throw SyntaxError(current_token, "Unexpected token");
    }
}


std::shared_ptr<Declaration> Parser::declaration()
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


std::shared_ptr<Conditional> Parser::conditional()
{
    shift(Token::Type::If);

    auto condition = expression();

    shift(Token::Type::Then);

    auto consequent = statements();

    decltype(statements()) alternative;

    if (current_token.type == Token::Type::Else)
    {
        shift(Token::Type::Else);
        alternative = statements();
    }

    shift(Token::Type::End);

    return std::make_shared<Conditional>(condition, consequent, alternative);
}


std::shared_ptr<WhileLoop> Parser::while_loop()
{
    shift(Token::Type::While);
    auto condition = expression();

    shift(Token::Type::Do);
    auto body = statements();
    shift(Token::Type::End);

    return std::make_shared<WhileLoop>(condition, body);
}


std::shared_ptr<Print> Parser::print()
{
    shift(Token::Type::Print);
    auto expr = expression();

    return std::make_shared<Print>(expr);
}


std::shared_ptr<Statements> Parser::statements()
{
    auto st = std::make_shared<Statements>();

    while (current_token.type != Token::Type::EndOfFile
           && current_token.type != Token::Type::Else
           && current_token.type != Token::Type::End)
    {
        st->statements.push_back(statement());
    }

    return st;
}
