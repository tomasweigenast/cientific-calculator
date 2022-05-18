#include <string>
#include <stdexcept>

struct AssertException : public std::runtime_error
{
    public:
        AssertException() = delete;
        AssertException(std::string assertName, std::string err) : std::runtime_error(assertName + ": " + err){}
};

struct TestCase
{
    private:
        std::string m_Name;

    public:
        TestCase() = delete;
        TestCase(const TestCase& other) : m_Name(other.m_Name){}
        TestCase(std::string name) : m_Name(name){}

        std::string get_name() const;

        void is_true(bool value);
        void is_false(bool value);
};