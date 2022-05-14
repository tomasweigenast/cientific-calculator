#include <token.h>
#include <string>
#include <sstream>

class Tokenizer {
    private:
        Token m_Token;
        double m_Number;
        std::istringstream& m_Input;
        char m_CurrentChar;
        std::string m_CurrentIdentifier;

    public:
        Tokenizer(std::istringstream& input) : m_Input(input) {
            next_char();
            next_token();
        }

        ~Tokenizer() {
        }
        
        Token get_token();
        double get_number();
        std::string get_current_identifier();
        void next_token();  
        void next_char();
};
