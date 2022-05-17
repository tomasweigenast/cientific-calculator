#include <util/id_generator.h>
#include <atomic>

static std::atomic_uint32_t _currentId;
std::string random_id() {
  _currentId++;
  return std::to_string(_currentId); 
}