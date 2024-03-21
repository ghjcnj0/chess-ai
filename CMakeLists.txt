cmake_minimum_required(VERSION 3.10)
project(chess-ai)

add_subdirectory(neural_network)
add_subdirectory(dependencies/conradsnicta/armadillo-code/armadillo-code-unstable)

add_executable(Chess_AI main.cpp)

target_link_libraries(Chess_AI Neural_Network armadillo)

include_directories(dependencies/xianyi/OpenBLAS/OpenBLAS-develop)


# моя дичь 


# путь к библиотекам LAPACK и BLAS
set(LAPACK_LIB_DIR "C:/Users/ARTEM/Desktop/VScode/qwer/lapack/lapack")
set(BLAS_LIB_DIR "C:/Users/ARTEM/Desktop/VScode/qwer/OpenBLAS/OpenBLAS")

# Найдем заголовочные файлы и библиотеки LAPACK и BLAS
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)

# Включим заголовочные файлы LAPACK
include_directories(${LAPACK_INCLUDE_DIRS})

# Добавим исполняемый файл вашего проекта
add_executable(YourExecutable main.cpp)

# Свяжем исполняемый файл с LAPACK и BLAS библиотеками
target_link_libraries(YourExecutable ${LAPACK_LIB_DIR}/lapack.lib ${BLAS_LIB_DIR}/OpenBLAS.lib)
