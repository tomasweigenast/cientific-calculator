#include <assert/assert.h>

std::string TestCase::get_name() const {
    return m_Name;
}

void TestCase::is_true(bool value) { if(!value) throw AssertException(m_Name, "value is not true."); }
void TestCase::is_false(bool value) { if(value) throw AssertException(m_Name, "value is not false."); }