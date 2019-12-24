add_executable(ctest_x ctest_test.cpp)

add_executable(ctest_f ctest_fail.cpp)

add_test(
  NAME ctest_test
  COMMAND $<TARGET_FILE:ctest_x>
  )

add_test(
  NAME ctest_fail
  COMMAND $<TARGET_FILE:ctest_f>
  )
