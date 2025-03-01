cmake_minimum_required(VERSION 3.15)

project(eigen-playground VERSION 1.0 DESCRIPTION "Learning Internal of Eigen" LANGUAGES CXX)

add_subdirectory(expression_templates)
add_subdirectory(aligned_allocation)
add_subdirectory(simd)
add_subdirectory(vector_addition)
add_subdirectory(vector_implementations)
add_subdirectory(valgrind)