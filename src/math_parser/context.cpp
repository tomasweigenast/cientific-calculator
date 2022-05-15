#include <math_parser/context.h>
#include <cmath>
#include <parser_exception/unknown_constant.h>
#include <parser_exception/invalid_argument.h>

double DefaultContext::resolve_constant(std::string name) {
    if(name == "pi") { 
        return M_PI;
    } else if(name == "e") {
        return M_E;
    }

    throw UnknownConstantException(name);
}

double DefaultContext::call_function(std::string name, double arguments[], unsigned int argumentCount) {
    if(name == "pow") {
        if(argumentCount != 2) {
            throw InvalidArgumentException("Expected two arguments.");
        }

        return pow(arguments[0], arguments[1]);
    } else if(name == "sqrt") {
        if(argumentCount != 2) {
            throw InvalidArgumentException("Expected two arguments.");
        }
        
        return pow(arguments[0], 1/arguments[1]);
    }
}