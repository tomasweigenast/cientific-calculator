#include <functional>
#include <string>

typedef std::function<double (double, double)> OperationExecutor;

struct MathOperation {
    private:
        std::string m_Operand;
        OperationExecutor m_Executor;

    public:
        MathOperation() = delete;
        MathOperation(std::string operand, OperationExecutor executor) 
            : m_Operand(operand), m_Executor(executor){}

        double execute(double a, double b);
};