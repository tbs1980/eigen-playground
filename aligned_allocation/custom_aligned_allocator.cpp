#include <iostream>
#include <memory>
#include <cstdlib>
#include <vector>

template <typename T, size_t Alignment>
class AlignedAllocator
{
public:
    using value_type = T;

    AlignedAllocator() = default;

    template <typename U>
    AlignedAllocator(const AlignedAllocator<U, Alignment> &) noexcept {}

    T *allocate(size_t n)
    {
        size_t size = n * sizeof(T);
        void *ptr = nullptr;

        if (size % Alignment != 0)
        {
            size += Alignment - (size % Alignment);
        }

        ptr = std::aligned_alloc(Alignment, size);

        if (!ptr)
        {
            throw std::bad_alloc();
        }

        return static_cast<T *>(ptr);
    }

    void deallocate(T *ptr) noexcept
    {
        std::free(ptr);
    }

    template <typename U>
    bool operator==(const AlignedAllocator<U, Alignment> &) const noexcept
    {
        return true;
    }

    template <typename U>
    bool operator!=(const AlignedAllocator<U, Alignment> &) const noexcept
    {
        return false;
    }
};

int main()
{
    const size_t alignment = 32;   // 256-bit alignment for AVX
    const size_t num_elements = 8; // Number of elements to allocate

    // Create an instance of AlignedAllocator
    AlignedAllocator<double, alignment> allocator;

    // Allocate memory for 8 doubles
    double *aligned_array = allocator.allocate(num_elements);

    // Verify alignment
    std::cout << "aligned_array is aligned: "
              << (reinterpret_cast<uintptr_t>(aligned_array) % alignment == 0)
              << std::endl;

    // Initialize the array
    for (size_t i = 0; i < num_elements; ++i)
    {
        aligned_array[i] = static_cast<double>(i); // Fill with values 0, 1, 2, ..., 7
    }

    // Print the array
    std::cout << "aligned_array: ";
    for (size_t i = 0; i < num_elements; ++i)
    {
        std::cout << aligned_array[i] << " ";
    }
    std::cout << std::endl;

    // Deallocate the memory
    allocator.deallocate(aligned_array);

    return 0;
}