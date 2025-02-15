add_executable(vector_addition vector_addition.cpp)
target_compile_features(vector_addition PUBLIC cxx_std_17)
target_compile_options(vector_addition PUBLIC -std=c++17 -mavx)