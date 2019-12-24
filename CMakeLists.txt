cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

enable_testing()

project(ds_verifier CXX)

include_directories(./src)
add_subdirectory(src)
