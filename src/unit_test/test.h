#include <exception>
#include <string>

#define STRINGFY(s) #s
#define TOSTRING(s) STRINGFY(s)
#define PREFIX __FILE__ ":" TOSTRING(__LINE__) ": "

struct test_error: std::exception {
  std::string message;
  test_error(const std::string& prefix, const std::string& message)
    : message(prefix + message) {}
  const char* what() const noexcept { return message.c_str(); }
};

#define TEST_ASSERT(boolean, message) \
  if(!(boolean)) { \
    throw test_error(PREFIX, message); \
  }
