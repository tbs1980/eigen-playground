#include <iostream>
#include <chrono>

#include "bench_array.hpp"
#include "naive_vector.hpp"

double time_naive_vector(std::size_t size)
{

    NaiveVector<float> x(size, 1.0f);
    NaiveVector<float> y(size, 2.0f);
    NaiveVector<float> z(size, 3.0f);
    NaiveVector<float> w(size, 4.0f);

    NaiveVector<float> res(size);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    res = x * x + y * y + z * z + w * w;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    double elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;

    return elapsed_time;
}

int main()
{
    std::size_t size = 1000000;
    std::size_t repeat = 100;

    double total_time_c_array = 0.0;
    double total_time_naive_vector = 0.0;

    for (std::size_t i = 0; i < repeat; ++i)
    {
        total_time_c_array += time_c_array(size);
        total_time_naive_vector += time_naive_vector(size);
    }

    std::cout << "Vector size = " << size << " and repetitions = " << repeat << std::endl;
    std::cout.precision(12);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);

    std::cout << "Avg time taken for computation (c array):     " << total_time_c_array / repeat << " secs\n";
    std::cout << "Avg time taken for computation (NaiveVector): " << total_time_naive_vector / repeat << " secs\n";
    return 0;
}