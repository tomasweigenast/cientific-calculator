#include <math_parser/context.h>
#include <cmath>
#include <parser_exception/unknown_constant.h>

double DefaultContext::resolve_variable(std::string name) {
    if(name == "pi") {
        return M_PI;
    } else if(name == "e") {
        return M_E;
    }

    throw UnknownConstantException(name);
}