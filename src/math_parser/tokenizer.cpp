#include <tokenizer.h>
#include <string>
#include <iostream>
#include <parser_exception/unexpected_char.h>

Token Tokenizer::get_token() {
    return this->m_Token;
}

double Tokenizer::get_number() {
    return this->m_Number;
}

std::string Tokenizer::get_current_identifier() {
    return this->m_CurrentIdentifier;
}

void Tokenizer::next_token() {
    
    // Skip whitespaces
    while(isspace(this->m_CurrentChar)) {
        this->next_char();
    }   

    // Special chars
    switch(this->m_CurrentChar) {
        case '\0':
        case ';':
            this->m_Token = EOL;
            return;

        case '+':
            this->next_char();
            this->m_Token = Add;
            return;

        case '-':
            this->next_char();
            this->m_Token = Subtract;
            return;

        case '*':
            this->next_char();
            this->m_Token = Multiply;
            return;

        case '/':
            this->next_char();
            this->m_Token = Divide;
            return;

        case '(':
            this->next_char();
            this->m_Token = OpenParens;
            return;

        case ')':
            this->next_char();
            this->m_Token = CloseParens;
            return;

        case ',':
            this->next_char();
            this->m_Token = Comma;
            return;
    }

    // is it a number?
    if(isdigit(this->m_CurrentChar) || this->m_CurrentChar == '.') {
        // Capture decimal points
        std::stringstream builder;
        bool haveDecimalPoint = false;
        
        while(isdigit(this->m_CurrentChar) || (!haveDecimalPoint && this->m_CurrentChar == '.')) {
            builder << this->m_CurrentChar;
            haveDecimalPoint = this->m_CurrentChar == '.';
            this->next_char();
        }

        std::string result = builder.str();

        // Parse it
        try {
            this->m_Number = atof(result.c_str()); 
            this->m_Token = Number;
        } catch(std::exception) {
            throw UnexpectedCharException("Invalid number constant.");
        }

        return;
    }

    // Constant or identifier. Starts with letter or underscore
    if(isalpha(this->m_CurrentChar) || this->m_CurrentChar == '_') {
        std::stringstream builder;

        // accept letter, digit or underscore
        while(isalpha(this->m_CurrentChar) || isdigit(this->m_CurrentChar) || m_CurrentChar == '_') {
            builder << this->m_CurrentChar;
            this->next_char();
        }

        this->m_CurrentIdentifier = builder.str();
        this->m_Token = Identifier;
        return;
    }

    throw UnexpectedCharException("Unexpected character.");
}

void Tokenizer::next_char() {
    try {
        char chr = this->m_Input.get();
        this->m_CurrentChar = chr;
    } catch(const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }

}