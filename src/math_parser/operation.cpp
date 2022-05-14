#include <math_parser/operation.h>

double MathOperation::execute(double a, double b) {
    return this->m_Executor(a, b);
}