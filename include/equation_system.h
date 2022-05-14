#include <vector>
#include <iostream>
#include <log.h>

struct Equation {
    private:
        std::string m_Statement;

    public:
        Equation() = delete;
        Equation(std::string statement) : m_Statement(statement){}

        std::string get_statement();
};

struct SystemEquation {
    private:
        int m_UnknownsCount;
        int m_EquationsCount;
        std::vector<Equation> m_Equations;


    public:
        SystemEquation(int unknownsCount) : 
            m_UnknownsCount(unknownsCount), 
            m_EquationsCount(unknownsCount * unknownsCount),
            m_Equations() {
                m_Equations.reserve(m_EquationsCount);
                printf("Created a new equation system with %d unknowns\n", unknownsCount);
                printf("Equations vector capacity: %ld - Size: %ld\n", m_Equations.capacity(), m_Equations.size());
            }

        SystemEquation() = delete;

        Equation equation_at(int index);
        int equation_count();
        int unknowns_count();
        
};