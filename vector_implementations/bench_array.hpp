#pragma once

#include <chrono>

double time_c_array(std::size_t size)
{

    float *x = new float[size];
    float *y = new float[size];
    float *z = new float[size];
    float *w = new float[size];

    for (std::size_t i = 0; i < size; ++i)
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
        z[i] = 3.0f;
        w[i] = 4.0f;
    }

    float *res = new float[size];

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (std::size_t i = 0; i < size; ++i)
    {
        res[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i] + w[i] * w[i];
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    double elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;

	delete[] res;

	delete[] x;
	delete[] y;
	delete[] z;
	delete[] w;

    return elapsed_time;
}