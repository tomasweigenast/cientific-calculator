#include <math_parser/context.h>
#include <cmath>
#include <parser_exception/unknown_constant.h>
#include <parser_exception/invalid_argument.h>

#define DEG_TO_RAD M_PI/180
#define RAD_TO_DEG 180/M_PI

DATATYPE DefaultContext::resolve_constant(std::string_view name) {
    if(name == "pi") { 
        return M_PI;
    } else if(name == "e") {
        return M_E;
    }

    throw UnknownConstantException(std::string(name));
}

DATATYPE DefaultContext::call_function(std::string_view name, DATATYPE arguments[], uint argumentCount) {
    if(name == "pow") {
        if(argumentCount != 2) {
            throw InvalidArgumentException("pow expects two arguments.");
        }

        return pow(arguments[0], arguments[1]);
    } else if(name == "sqrt") {
        if(argumentCount != 2) {
            throw InvalidArgumentException("sqrt expects two arguments.");
        }
        
        return pow(arguments[0], 1/arguments[1]);
    } else if(name == "sin") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("sin expects one argument.");
        }

        return sin(arguments[0]);
    } else if(name == "cos") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("cos expects one argument.");
        }

        return cos(arguments[0]);
    } else if(name == "tan") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("tan expects one argument.");
        }

        return tan(arguments[0]);
    } else if(name == "asin") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("asin expects one argument.");
        }

        return asin(arguments[0]);
    } else if(name == "acos") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("acos expects one argument.");
        }

        return acos(arguments[0]);
    } else if(name == "atan") {
        if(argumentCount != 1) {
            throw InvalidArgumentException("atan expects one argument.");
        }

        return atan(arguments[0]);
    } else if(name == "sum") {
        if(argumentCount != 3) {
            throw InvalidArgumentException("sum expects three arguments.");
        }

        // TODO: add check to avoid decimal numbers in 'n' and 'i' variables

        // double i = arguments[0]; // desde donde empieza
        // int n = arguments[1]; // hasta donde llega la sumatoria

        // int results[n];
        // for(int i = arguments[0]; i < n; i++) {
            
        // }
    }

    throw UnknownFunctionException(std::string(name));
}

DATATYPE VariableContext::resolve_constant(std::string_view name) {
    try {
        return DefaultContext::resolve_constant(name);
    } catch (const UnknownConstantException& ex) {
        if(name[0] == this->m_VariableName) {
            return this->m_VariableValue;
        }

        throw UnknownVariableException(std::string(name));
    }
}

DATATYPE VariableContext::variable_value() const {
    return this->m_VariableValue;
}

void VariableContext::set_variable_value(DATATYPE newValue)
{
    m_VariableValue = newValue;
}
