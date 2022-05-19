#include <math_parser/parser.h>

struct Summation
{
    private:
        Node* m_Ecuation;
        uint32_t m_From;
        uint32_t m_To;

    public:
        Summation() = delete;
        Summation(const Summation& other) : m_Ecuation(other.m_Ecuation), m_From(other.m_From), m_To(other.m_To){}
        Summation(Node* ecuation, uint32_t from, uint32_t to) : m_Ecuation(ecuation), m_From(from), m_To(to) {}
        ~Summation()
        {
            delete m_Ecuation;
            std::cout << "Deleting summation" << std::endl;
        }

        DATATYPE evaluate();
};