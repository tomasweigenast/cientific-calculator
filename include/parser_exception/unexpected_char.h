#include <stdexcept>

struct UnexpectedCharException : public std::runtime_error {
    public:
        UnexpectedCharException() = delete;
        UnexpectedCharException(const char* err) : std::runtime_error(err){}
};  