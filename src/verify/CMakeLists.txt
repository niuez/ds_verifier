add_executable(accum_verify accumlation_verify.cpp)

add_test(
  NAME accum_verify
  COMMAND $<TARGET_FILE:accum_verify>
  )

