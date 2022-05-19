#include <summation/summation.h>

DATATYPE Summation::evaluate()
{
    DATATYPE result = 0;

    VariableContext* context = new VariableContext('x');
    for(uint32_t i = m_From; i <= m_To; i++)
    {
        context->set_variable_value(i);
        result += m_Ecuation->eval(context);
    }

    delete context;

    return result;
}