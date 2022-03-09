cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(regular structure/scanner_re.cpp structure/scanner_re.h structure/parser_re.cpp structure/parser_re.h
        re-tree/tree4re.cpp re-tree/tree4re.h re-tree/tree_creator.h re-tree/tree_creator.cpp)