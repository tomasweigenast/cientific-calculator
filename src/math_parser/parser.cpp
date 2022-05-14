#include <math_parser/parser.h>
#include <parser_exception/unexpected_char.h>
#include <iostream>

Node* Parser::parse_expression() {
    Node* expression = this->parse_add_subtract();

    if(this->m_Tokenizer.get_token() != EOL) {
        throw UnexpectedCharException("Unexpected characters at end of expression.");
    }

    return expression;
}

Node* Parser::parse_add_subtract() {
    // parse left hand side
    Node* lhs = this->parse_multiply_divide();

    while(true) {
        MathOperation* operation;
        bool opFound = false;
        
        switch(this->m_Tokenizer.get_token()) {
            case Add:
                operation = new MathOperation("+", [](double a, double b) -> double {
                    return a+b;
                });
                opFound = true;
                break;

            case Subtract:
                operation = new MathOperation("-", [](double a, double b) -> double {
                    return a-b;
                });
                opFound = true;
                break;

            default:
                break;
        }

        // Binary operator not found
        if(!opFound) {
            return lhs;
        }

        // Skip the operator
        this->m_Tokenizer.next_token();

        // Parse the right hand side of the expression
        Node* rhs = this->parse_multiply_divide();

        // Create a binary node and use it as the left-hand side now on
        lhs = new BinaryNode(lhs, rhs, operation);
    }
}

Node* Parser::parse_multiply_divide() {
    // parse left hand side
    Node* lhs = this->parse_unary();

    while(true) {
        MathOperation* operation;
        bool opFound = false;
        
        switch(this->m_Tokenizer.get_token()) {
            case Multiply:
                operation = new MathOperation("*", [](double a, double b) -> double {
                    return a*b;
                });
                opFound = true;
                break;

            case Divide:
                operation = new MathOperation("/", [](double a, double b) -> double {
                    return a/b;
                });
                opFound = true;
                break;

            default:
                break;
        }

        // Binary operator not found
        if(!opFound) {
            return lhs;
        }

        // Skip the operator
        this->m_Tokenizer.next_token();

        // Parse the right hand side of the expression
        Node* rhs = this->parse_unary();

        // Create a binary node and use it as the left-hand side now on
        lhs = new BinaryNode(lhs, rhs, operation);
    }
}

Node* Parser::parse_unary() {

    // Skip + because its no-op
    if(this->m_Tokenizer.get_token() == Add) {
        this->m_Tokenizer.next_token();
        return this->parse_unary();
    }

    // Negative operator
    if(this->m_Tokenizer.get_token() == Subtract){
        // Skip the token
        this->m_Tokenizer.next_token();

        // parse right side
        // this must recurse itself to support negative of negative
        Node* rhs = this->parse_unary();

        // Create the unary node
        return new UnaryNode(rhs, new MathOperation("+", [](double a, double b) -> double {
            return -b;
        }));
    }

    // No positive/negative operator so parse a leaf node
    return this->parse_leaf();
}

Node* Parser::parse_leaf() {
    // Is it a number?
    if(this->m_Tokenizer.get_token() == Number) {
        Node* node = new NumberNode(this->m_Tokenizer.get_number());
        this->m_Tokenizer.next_token();
        return node;
    }

    // Is it a parenthesis?
    if(this->m_Tokenizer.get_token() == OpenParens) {
        // Skip the '('
        this->m_Tokenizer.next_token();

        // Parse the top-level expression
        Node* node = this->parse_add_subtract();

        // Check and skip ')'
        if(this->m_Tokenizer.get_token() != CloseParens) {
            throw UnexpectedCharException("Expected close parenthesis.");
        }

        this->m_Tokenizer.next_token();
        return node;
    }

    // Is it a variable?
    if(this->m_Tokenizer.get_token() == Identifier) {
        Node* node = new ConstantNode(this->m_Tokenizer.get_current_identifier());
        this->m_Tokenizer.next_token();
        return node;
    }
    
    throw UnexpectedCharException("Unexpected token: " + this->m_Tokenizer.get_token());
}