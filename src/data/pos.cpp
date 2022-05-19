#include <data/pos.h>

uint8_t Pos::get_i() {
    return m_i;
}

uint8_t Pos::get_j() {
    return m_j;
}

void Pos::set_i(uint8_t i)
{
    m_i = i;
}

void Pos::set_j(uint8_t j)
{
    m_j = j;
}

void Pos::set(uint8_t i, uint8_t j)
{
    m_i = i;
    m_j = j;
}