#include <memory>

struct Pos 
{
    private:
        uint8_t m_i;
        uint8_t m_j;

    public:
        Pos() = delete;
        Pos(const Pos& other) : m_i(other.m_i), m_j(other.m_j) {}
        Pos(uint8_t i, uint8_t j) : m_i(i), m_j(j) {}

        uint8_t get_i();
        uint8_t get_j();

        void set_i(uint8_t i);
        void set_j(uint8_t j);
        void set(uint8_t i, uint8_t j);
};