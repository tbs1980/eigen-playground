add_executable(check_gcc_intel_simd.cpp check_gcc_intel_simd.cpp)
add_executable(avx_vector_addition avx_vector_addition.cpp)
target_compile_features(avx_vector_addition PUBLIC cxx_std_17)
target_compile_options(avx_vector_addition PRIVATE -mavx)