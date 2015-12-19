cmake_minimum_required(VERSION 3.3)
project(llvm_kaleidescope)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall")

set(SOURCE_FILES lexer.cpp global.h driver.cpp parser.cpp)
add_executable(llvm_kaleidescope ${SOURCE_FILES})