add_subdirectory(array_wrapper)

add_executable(ctest_x ctest_test.cpp)

add_test(
  NAME ctest_test
  COMMAND $<TARGET_FILE:ctest_x>
  )

