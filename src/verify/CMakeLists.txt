add_executable(accum_verify accumlation_verify.cpp)
target_link_libraries(accum_verify ds_verifier)

file(GLOB_RECURSE verify_source_list *_verify.cpp)

set(verify_list)
file(REMOVE "${CMAKE_BINARY_DIR}/verify_list")

foreach(verify_source IN LISTS verify_source_list)
  file(RELATIVE_PATH relative_source "${CMAKE_SOURCE_DIR}" "${verify_source}")
  message("verify_source: ${relative_source}")
  get_filename_component(verify_target "${verify_source}" NAME_WE)
  add_executable("${verify_target}" "${verify_source}")
  target_link_libraries("${verify_target}" ds_verifier)
  list(APPEND verify_list "${verify_target}")
  file(APPEND "${CMAKE_BINARY_DIR}/verify_list" "${CMAKE_CURRENT_BINARY_DIR}/${verify_target}:${relative_source}\n")
endforeach()
