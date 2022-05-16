/*#include <vector>
#include <node.h>

struct FunctionArguments {
    private:
        std::vector<Node*>& m_Arguments;
        double* m_EvaluatedArguments;
        unsigned int m_ArgumentsCount;

    public:
        FunctionArguments() = delete; 
        FunctionArguments(const FunctionArguments&) = delete;
        FunctionArguments(Context *context, std::vector<Node*>& arguments) 
            : m_Arguments(arguments), m_ArgumentsCount(arguments.size()) {
            m_EvaluatedArguments = new double[m_ArgumentsCount];

            for(int i = 0; i < this->m_ArgumentsCount; i++) {
                m_EvaluatedArguments[i] = this->m_Arguments[i]->eval(context);
            }

        }

        ~FunctionArguments() {
            delete[] m_EvaluatedArguments;
        }

        const std::vector<Node*>& arguments();
        const double* evaluated_arguments();
        const unsigned int argument_count();

        double const& operator[](int index) const {
            return m_EvaluatedArguments[index];
        }
};*/