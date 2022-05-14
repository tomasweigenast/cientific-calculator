#include <string>

struct Context {
    public:
        virtual double resolve_variable(std::string name) = 0;
};

struct DefaultContext : public Context {
    public:
        double resolve_variable(std::string name);
};