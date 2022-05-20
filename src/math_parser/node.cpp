#include <math_parser/node.h>

DATATYPE NumberNode::eval(Context *context) {
    (void)context;
    return this->m_Number;
}

DATATYPE BinaryNode::eval(Context *context) {
    DATATYPE left = this->m_Left->eval(context);
    DATATYPE right = this->m_Right->eval(context);

    DATATYPE result = (*this->m_Operation)(left, right);
    return result;
}

DATATYPE UnaryNode::eval(Context *context) {
    DATATYPE right = this->m_Right->eval(context);
    
    DATATYPE result = (*this->m_Operation)(right);
    return result;
}

DATATYPE ConstantNode::eval(Context *context) {
    return context->resolve_constant(this->m_ConstantName);
}

DATATYPE FunctionNode::eval(Context *context) {
    DATATYPE* arguments = new DATATYPE[this->m_Arguments.size()];

    for(uint i = 0; i < this->m_Arguments.size(); i++) {
        arguments[i] = this->m_Arguments[i]->eval(context);
    }

    // Call the function
    return context->call_function(this->m_FunctionName, arguments, this->m_Arguments.size());
}