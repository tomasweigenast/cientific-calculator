#include <stdexcept>

struct UnknownConstantException : public std::runtime_error {
    public:
        UnknownConstantException() = delete;
        UnknownConstantException(std::string constName) : std::runtime_error("Unknown constant: " + constName){}
};  

struct UnknownVariableException : public std::runtime_error {
    public:
        UnknownVariableException() = delete;
        UnknownVariableException(std::string constName) : std::runtime_error("Unknown variable: " + constName){}
};  