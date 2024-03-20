cmake_minimum_required(VERSION 3.10)
project(chess-ai)

add_subdirectory(neural_network)
add_subdirectory(dependencies/conradsnicta/armadillo-code/armadillo-code-unstable)
add_subdirectory(dependencies/OpenMathLib/OpenBLAS/OpenBLAS-develop)

add_executable(Chess_AI main.cpp)

target_link_libraries(Chess_AI Neural_Network armadillo openblas)

include_directories(dependencies/OpenMathLib/OpenBLAS/OpenBLAS-develop)