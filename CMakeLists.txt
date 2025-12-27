cmake_minimum_required(VERSION 3.5)
project(thought-mapper)

file(GLOB_RECURSE sources include/* src/* main.cpp)

add_executable(tmApp ${sources})

target_compile_options(tmApp PUBLIC -std=c++17 -Wall -Wfloat-conversion -g)

install(TARGETS tmApp DESTINATION ./build/)

set(CPACK_PACKAGE_NAME "thought-mapper")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)
