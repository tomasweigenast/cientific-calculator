#include <operation.h>
#include <context.h>
#include <vector>
#include <iostream>

struct Node {
    public:
        Node()
        {
            std::cout << "Node created." << std::endl;
        }
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
        NumberNode(DATATYPE number) : m_Number(number) 
        {
            std::cout << "NumberNode created." << std::endl;
        }
        ~NumberNode() {
            std::cout << "NumberNode deleted." << std::endl;
        }

        DATATYPE eval(Context *context);

};

struct BinaryNode : public Node {
    private:
        Node *m_Left;
        Node *m_Right;
        const BinaryExecutor& m_Operation;

    public:
        BinaryNode() = delete;
        BinaryNode(Node *left, Node *right, const BinaryExecutor& operation) 
            : m_Left(left), m_Right(right), m_Operation(operation) 
            {
                std::cout << "Binary node created." << std::endl;
            }
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
        const UnaryExecutor& m_Operation;

    public:
        UnaryNode() = delete;
        UnaryNode(Node *right, const UnaryExecutor& operation) 
            : m_Right(right), m_Operation(operation)
            {
                std::cout << "UnaryNode created." << std::endl;
            }
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