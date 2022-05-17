#include <data/pos.h>

unsigned int Pos::get_i() {
    return m_i;
}

unsigned int Pos::get_j() {
    return m_j;
}

void Pos::set_i(unsigned int i)
{
    m_i = i;
}

void Pos::set_j(unsigned int j)
{
    m_j = j;
}

void Pos::set(unsigned int i, unsigned int j)
{
    m_i = i;
    m_j = j;
}