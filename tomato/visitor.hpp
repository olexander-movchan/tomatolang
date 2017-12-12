#ifndef TOMATO_VISITOR_HPP
#define TOMATO_VISITOR_HPP


namespace Tomato::Syntax
{
    class Visitor
    {
    public:
        void visit(struct ASTNode &node);

        virtual void process(struct StatementBlock   &node) = 0;

        virtual void process(struct Identifier            &node) = 0;
        virtual void process(struct Literal               &node) = 0;
        virtual void process(struct BinaryOperation       &node) = 0;
        virtual void process(struct UnaryOperation        &node) = 0;
        virtual void process(struct Indexation            &node) = 0;
        virtual void process(struct Call                  &node) = 0;
        virtual void process(struct MemberAccess          &node) = 0;

        virtual void process(struct ConditionalStatement  &node) = 0;
        virtual void process(struct ConditionalLoop       &node) = 0;

        virtual void process(struct PrintStatement        &node) = 0;
        virtual void process(struct ReadStatement         &node) = 0;

        virtual void process(struct InvalidStatement      &node) = 0;
    };
}


#endif //TOMATOLANG_VISITOR_HPP
