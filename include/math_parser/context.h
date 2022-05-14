#include <string>

struct Context {
    public:
        virtual double resolve_constant(std::string name) = 0;
};

struct DefaultContext : public Context {
    public:
        double resolve_constant(std::string name);
};