#include <math_parser/node.h>

double NumberNode::eval(Context *context) {
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
    // Evaluate all arguments
    double argumentValues[this->m_ArgumentsSize];
    for(int i = 0; i < this->m_ArgumentsSize; i++) {
        argumentValues[i] = this->m_Arguments[i]->eval(context);
    }

    // Call the function
    return context->call_function(this->m_FunctionName, argumentValues);
}