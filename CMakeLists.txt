cmake_minimum_required(VERSION 3.3)
project(llvm_kaleidescope)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lexer.cpp global.h)
add_executable(llvm_kaleidescope ${SOURCE_FILES})