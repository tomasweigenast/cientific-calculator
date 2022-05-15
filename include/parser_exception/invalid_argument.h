#include <stdexcept>

struct InvalidArgumentException : public std::runtime_error {
    public:
        InvalidArgumentException() = delete;
        InvalidArgumentException(const char* err) : std::runtime_error(err){}
};  