#include <math_parser/context.h>
#include <cmath>
#include <parser_exception/unknown_constant.h>

double DefaultContext::resolve_constant(std::string name) {
    if(name == "pi") {
        return M_PI;
    } else if(name == "e") {
        return M_E;
    }

    throw UnknownConstantException(name);
}

double DefaultContext::call_function(std::string name, double arguments[]) {
    
}