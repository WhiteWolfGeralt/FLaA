cmake_minimum_required(VERSION 3.16)
project(grammar)

set(CMAKE_CXX_STANDARD 14)

add_library(grammar structure/scanner_gr.h structure/scanner_gr.cpp structure/parser_gr.cpp structure/parser_gr.h)