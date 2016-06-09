cmake_minimum_required(VERSION 3.1.0)

project(Kaleidescope CXX)

add_executable(kaleidescope main.cpp Lexer.cpp AST.cpp Parser.cpp)
set_property(TARGET kaleidescope PROPERTY CXX_STANDARD 11)
set_property(TARGET kaleidescope PROPERTY CXX_STANDARD_REQUIRED ON)


