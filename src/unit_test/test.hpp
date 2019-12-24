#ifndef UNIT_TEST_TEST_HPP
#define UNIT_TEST_TEST_HPP

#include <exception>
#include <string>
#include <iostream>

#define STRINGFY(s) #s
#define TOSTRING(s) STRINGFY(s)
#define PREFIX __FILE__ ":" TOSTRING(__LINE__) ": "

struct test_error: std::exception {
  std::string message;
  test_error(const std::string& prefix, const std::string& message)
    : message(prefix + message) {}
  const char* what() const noexcept { return message.c_str(); }
};

#define TEST_START() \
  int main() { \
    try

#define TEST_END() \
    catch(test_error e){ \
      std::cout << "[ Failure ] : " << e.what() << std::endl; \
      return 1; \
    } \
    std::cout << "[ Passed ]" << std::endl; \
    return 0; \
  }
#define TEST_ASSERT(boolean, message) \
  if(!(boolean)) { \
    throw test_error(PREFIX, message); \
  }
#endif
