#include <gtest/gtest.h>
#include <syntax/parser.hpp>
#include <errors.hpp>


using namespace Tomato;


TEST(ParserTest, Expressions)
{
    Parser parser;

    ASSERT_NO_THROW(parser.parse("0"));
    ASSERT_NO_THROW(parser.parse("2.0"));
    ASSERT_NO_THROW(parser.parse("foo"));
    ASSERT_NO_THROW(parser.parse("not bar"));
    ASSERT_NO_THROW(parser.parse("2 + 3"));
    ASSERT_NO_THROW(parser.parse("2 + 3 * 2"));
    ASSERT_NO_THROW(parser.parse("2 + 3 * -(2 - bar) ^ 4"));
    ASSERT_NO_THROW(parser.parse("a < b and b < c"));

    ASSERT_THROW(parser.parse("2 +"),    SyntaxError);
    ASSERT_THROW(parser.parse("2 + / 3"), SyntaxError);
    ASSERT_THROW(parser.parse("2 ^^ 3"),  SyntaxError);
    ASSERT_THROW(parser.parse("and 2 3"), SyntaxError);

    ASSERT_EQ(typeid(*parser.parse("2 * 2 + 2")), typeid(AST::StatementListNode));
    ASSERT_EQ(typeid(*parser.expression("2 * 2 + 2")), typeid(AST::BinaryOperatorNode));
}


class SyntaxVisitor : private AST::Visitor
{
public:
    std::vector<AST::AbstractNode *> traverse(AST::AbstractNode &tree)
    {
        nodes.clear();
        AST::Visitor::visit(tree);
        return nodes;
    }

private:
    void visit(AST::StatementListNode   &node) override
    {
        nodes.push_back(&node);

        for (auto &statement : node.statements)
        {
            AST::Visitor::visit(*statement);
        }
    }

    void visit(AST::PrintNode           &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.expression);
    }

    void visit(AST::AssignmentNode      &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.destination);
        AST::Visitor::visit(*node.source);
    }

    void visit(AST::DeclarationNode     &node) override
    {
        nodes.push_back(&node);

        visit(*node.variable);
        AST::Visitor::visit(*node.initializer);
    }

    void visit(AST::BinaryOperatorNode  &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.left);
        AST::Visitor::visit(*node.right);
    }

    void visit(AST::UnaryOperatorNode   &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.expression);
    }

    void visit(AST::IdentifierNode      &node) override
    {
        nodes.push_back(&node);
    }

    void visit(AST::LiteralNode         &node) override
    {
        nodes.push_back(&node);
    }

    void visit(AST::ConditionalNode     &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.condition);
        visit(*node.consequent);
        visit(*node.alternative);
    }

    void visit(AST::LoopNode            &node) override
    {
        nodes.push_back(&node);

        AST::Visitor::visit(*node.condition);
        visit(*node.statements);
    }

private:
    std::vector<AST::AbstractNode *> nodes;
};


TEST(ParserTest, SyntaxTree)
{
    Parser parser;
    SyntaxVisitor s;

    auto treeA = parser.parse("2 + 2 * x");
    auto listA = s.traverse(*treeA);

    ASSERT_STREQ(typeid(*listA[0]).name(), typeid(AST::StatementListNode).name());
    ASSERT_STREQ(typeid(*listA[1]).name(), typeid(AST::BinaryOperatorNode).name());
    ASSERT_STREQ(typeid(*listA[2]).name(), typeid(AST::LiteralNode).name());
    ASSERT_STREQ(typeid(*listA[3]).name(), typeid(AST::BinaryOperatorNode).name());
    ASSERT_STREQ(typeid(*listA[4]).name(), typeid(AST::LiteralNode).name());
    ASSERT_STREQ(typeid(*listA[5]).name(), typeid(AST::IdentifierNode).name());
}
