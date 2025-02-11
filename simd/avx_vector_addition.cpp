#include <iostream>
#include <immintrin.h>

int main()
{
    const int size = 8; // Number of elements in the array
    alignas(32) double a[size] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    alignas(32) double b[size] = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    alignas(32) double c[size]; // Result array

    // Vector addition usig AVX instructions
    for (int i = 0; i < size; i += 4)
    {
        __m256d va = _mm256_load_pd(&a[i]); // Load 4 doubles from array a
        __m256d vb = _mm256_load_pd(&b[i]); // Load 4 doubles from array b
        __m256d vc = _mm256_add_pd(va, vb); // Add 4 doubles
        _mm256_store_pd(&c[i], vc);         // Store the results to c
    }

    // Print results
    for (int i = 0; i < size; ++i)
    {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}