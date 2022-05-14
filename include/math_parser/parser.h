#include <tokenizer.h>
#include <node.h>

struct Parser {
    private:
        Tokenizer &m_Tokenizer;

    public:
        Parser() = delete;
        Parser(Tokenizer &tokenizer) : m_Tokenizer(tokenizer) {}

        Node* parse_expression();
        Node* parse_add_subtract();
        Node* parse_multiply_divide();
        Node* parse_unary();
        Node* parse_leaf();
};