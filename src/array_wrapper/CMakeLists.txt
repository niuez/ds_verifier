add_executable(array_wrapper_vector_test vector_test.cpp)
add_test(
  NAME array_wrapper_vector_test
  COMMAND $<TARGET_FILE:array_wrapper_vector_test>
  )

add_executable(array_wrapper_accum_test accumlation_test.cpp)
add_test(
  NAME array+wrapper_accum_test
  COMMAND $<TARGET_FILE:array_wrapper_accum_test>
  )
