#include <string>

struct Context {
    public:
        virtual double resolve_constant(std::string name) = 0;
        virtual double call_function(std::string name, double arguments[], unsigned int argumentCount) = 0;
};

struct DefaultContext : public Context {
    public:
        double resolve_constant(std::string name);
        double call_function(std::string name, double arguments[], unsigned int argumentCount);
};