#include <math_parser/context.h>
#include <cmath>
#include <parser_exception/unknown_constant.h>
#include <parser_exception/invalid_argument.h>

#define DEG_TO_RAD M_PI/180
#define RAD_TO_DEG 180/M_PI

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
    }
}