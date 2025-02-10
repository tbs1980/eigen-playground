#include <iostream>

// https://gcc.gnu.org/onlinedocs/gcc/x86-Built-in-Functions.html

int main()
{
    std::cout << __builtin_cpu_supports("sse") << std::endl;
    std::cout << __builtin_cpu_supports("sse2") << std::endl;
    std::cout << __builtin_cpu_supports("avx") << std::endl;
    std::cout << __builtin_cpu_supports("avx2") << std::endl;
    std::cout << __builtin_cpu_supports("avx512f") << std::endl;

    return 0;
}