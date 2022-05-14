#include <string>
#include <equation_system.h>

std::string Equation::get_statement() {
    return this->m_Statement;
}

Equation SystemEquation::equation_at(int index) {
    return this->m_Equations.at(index);
}

int SystemEquation::equation_count() {
    return this->m_EquationsCount;
}

int SystemEquation::unknowns_count() {
    return this->m_UnknownsCount;
}