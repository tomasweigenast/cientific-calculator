#include <string>
#include <vector>
#include <app.h>

struct Context {
    public:
        virtual DATATYPE resolve_constant(std::string_view name) = 0;
        virtual DATATYPE call_function(std::string_view name, DATATYPE arguments[], uint argumentCount) = 0;
};

struct DefaultContext : public Context {
    public:
        DATATYPE resolve_constant(std::string_view name);
        DATATYPE call_function(std::string_view name, DATATYPE arguments[], uint argumentCount);
};

struct VariableContext : public DefaultContext {
    private: 
        DATATYPE m_VariableValue;
        const char& m_VariableName;

    public:
        VariableContext() = delete;
        VariableContext(const VariableContext&) = delete;
        VariableContext(DATATYPE variableValue, const char& variableName) : m_VariableValue(variableValue), m_VariableName(variableName){}
        VariableContext(const char& variableName) : m_VariableName(variableName) {}

        DATATYPE resolve_constant(std::string_view name) override;
        DATATYPE variable_value() const;
        void set_variable_value(DATATYPE newValue);
};