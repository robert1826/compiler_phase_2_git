cmake_minimum_required(VERSION 2.6)
project(compiler_phase_2)
SET(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(compiler_phase_2 main.cpp First_Follow_calc.cpp InputReader.cpp Lexical_Dummy.cpp Parser.cpp TableBuilder.cpp Eliminate_left_recursion.cpp Matcher.cpp)

install(TARGETS compiler_phase_2 RUNTIME DESTINATION bin)
