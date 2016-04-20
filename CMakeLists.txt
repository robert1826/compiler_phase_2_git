cmake_minimum_required(VERSION 2.6)
project(compiler_phase_2)

add_executable(compiler_phase_2 main.cpp)

install(TARGETS compiler_phase_2 RUNTIME DESTINATION bin)
