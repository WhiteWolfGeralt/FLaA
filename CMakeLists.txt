cmake_minimum_required(VERSION 3.16)
project(FLaA_analyzer VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/grammar)
add_subdirectory(src/regular)
add_subdirectory(src/tree)

add_executable(FLaA_analyzer main.cpp)
target_link_libraries(FLaA_analyzer grammar)
target_link_libraries(FLaA_analyzer regular)
target_link_libraries(FLaA_analyzer tree)