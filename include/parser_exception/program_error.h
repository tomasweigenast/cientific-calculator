#include <stdexcept>

struct ProgramException : public std::runtime_error {
    public:
        ProgramException() = delete;
        ProgramException(const char* err) : std::runtime_error(err){}
};  