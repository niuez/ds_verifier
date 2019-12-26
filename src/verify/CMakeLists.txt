add_executable(accum_verify accumlation_verify.cpp)

target_link_libraries(accum_verify ds_verifier)

add_test(
  NAME accum_verify
  COMMAND $<TARGET_FILE:accum_verify>
  )

