#include <operation.h>
#include <context.h>
#include <vector>
#include <iostream>

struct Node {
    public:
        virtual ~Node(){
            std::cout << "Node deleted." << std::endl;
        };

        virtual DATATYPE eval(Context *context) = 0;
};

struct NumberNode : public Node {
    private:
        DATATYPE m_Number;

    public:
        NumberNode() = delete;
        NumberNode(DATATYPE number) : m_Number(number) {}
        ~NumberNode() {
            std::cout << "NumberNode deleted." << std::endl;
        }

        DATATYPE eval(Context *context);

};

struct BinaryNode : public Node {
    private:
        Node *m_Left;
        Node *m_Right;
        BinaryExecutor* m_Operation;

    public:
        BinaryNode() = delete;
        BinaryNode(Node *left, Node *right, BinaryExecutor* operation) 
            : m_Left(left), m_Right(right), m_Operation(operation) {}
        ~BinaryNode() {
            delete m_Left;
            delete m_Right;
            std::cout << "BinaryNode deleted." << std::endl;
        }

        DATATYPE eval(Context *context);
};

struct UnaryNode : public Node {
    private:
        Node *m_Right;
        UnaryExecutor* m_Operation;

    public:
        UnaryNode() = delete;
        UnaryNode(Node *right, UnaryExecutor* operation) 
            : m_Right(right), m_Operation(operation){}
        ~UnaryNode() {
            delete m_Right;
            std::cout << "UnaryNode deleted." << std::endl;
        }

        DATATYPE eval(Context *context);

};

struct ConstantNode : public Node {
    private:
        std::string m_ConstantName;

    public:
        ConstantNode() = delete;
        ConstantNode(std::string constantName) : m_ConstantName(constantName){}
        ~ConstantNode() {}

        DATATYPE eval(Context *context);
};

struct FunctionNode : public Node {
    private:
        std::string_view m_FunctionName;
        std::vector<Node*> m_Arguments;

    public:
        FunctionNode() = delete;
        FunctionNode(const FunctionNode&) = delete;
        FunctionNode(std::string_view functionName, std::vector<Node*> arguments) : m_FunctionName(functionName), m_Arguments(arguments) {}
        ~FunctionNode() {
            for(Node* n : m_Arguments) {
                delete n;
            }

            m_Arguments.clear();
        }

        DATATYPE eval(Context *context);
};