#include <string>
#include <vector>

struct Context {
    public:
        virtual double resolve_constant(std::string name) = 0;
        virtual double call_function(std::string name, double arguments[], unsigned int argumentCount) = 0;
};

struct DefaultContext : public Context {
    public:
        double resolve_constant(std::string name);
        double call_function(std::string name, double arguments[], unsigned int argumentCount);
};

struct VariableContext : public DefaultContext {
    private: 
        double m_VariableValue;
        std::string m_VariableName;

    public:
        VariableContext() = delete;
        VariableContext(const VariableContext&) = delete;
        VariableContext(double variableValue, std::string variableName) : m_VariableValue(variableValue), m_VariableName(variableName){}

        double resolve_constant(std::string name);
        double call_function(std::string name, double arguments[], unsigned int argumentCount);
};