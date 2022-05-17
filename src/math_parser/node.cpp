#include <math_parser/node.h>

double NumberNode::eval(Context *context) {
    (void)context;
    return this->m_Number;
}

double BinaryNode::eval(Context *context) {
    double left = this->m_Left->eval(context);
    double right = this->m_Right->eval(context);

    double result = this->m_Operation->execute(left, right);
    return result;
}

double UnaryNode::eval(Context *context) {
    double right = this->m_Right->eval(context);
    
    double result = this->m_Operation->execute(0, right);
    return result;
}

double ConstantNode::eval(Context *context) {
    return context->resolve_constant(this->m_ConstantName);
}

double FunctionNode::eval(Context *context) {
    double* arguments = new double[this->m_Arguments.size()];

    for(unsigned int i = 0; i < this->m_Arguments.size(); i++) {
        arguments[i] = this->m_Arguments[i]->eval(context);
    }

    // Call the function
    return context->call_function(this->m_FunctionName, arguments, this->m_Arguments.size());
}