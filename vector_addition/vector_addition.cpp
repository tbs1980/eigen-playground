#include <iostream>
#include <memory>      // For std::unique_ptr and std::align
#include <immintrin.h> // For AVX and SSE intrinsics
#include <type_traits> // For std::conditional
#include <cstdlib>

// Define a custom aligned allocator
// Also see custom_aligned_allocator.cpp
template <typename T, size_t Alignment>
class AlignedAllocator
{
public:
    using value_type = T;

    AlignedAllocator() = default;

    template <typename U>
    AlignedAllocator(const AlignedAllocator<U, Alignment> &) noexcept {}

    static T *allocate(size_t n)
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

    static void deallocate(T *ptr) noexcept
    {
        std::free(ptr);
    }
};

// Default implementation (scalar fallback)
template <typename Scalar>
struct SimdTraits
{
    using Packet = Scalar;
    static constexpr size_t PacketSize = 1;

    static Packet load(const Scalar *from) { return *from; }
    static void store(Scalar *to, Packet packet) { *to = packet; }
    static Packet add(Packet a, Packet b) { return a + b; }
};

// Specialize for AVX (256-bit registers, 4 doubles)
#ifdef __AVX__
template <>
struct SimdTraits<double>
{
    using Packet = __m256d;
    static constexpr size_t PacketSize = 4;

    static Packet load(const double *from) { return _mm256_load_pd(from); }
    static void store(double *to, Packet packet) { _mm256_store_pd(to, packet); }
    static Packet add(Packet a, Packet b) { return _mm256_add_pd(a, b); }
};
#endif

// Specialize for SSE (128-bit registers, 2 doubles)
#ifdef __SSE2__
#ifndef __AVX__
template <>
struct SimdTraits<double>
{
    using Packet = __m128d;
    static constexpr size_t PacketSize = 2;

    static Packet load(const double *from) { return _mm_load_pd(from); }
    static void store(double *to, Packet packet) { _mm_store_pd(to, packet); }
    static Packet add(Packet a, Packet b) { return _mm_add_pd(a, b); }
};
#endif
#endif

// Vector class with aligned memory allocation
template <typename Scalar, size_t Alignment = 32>
class Vector
{
public:
    using AlignedAlloc = AlignedAllocator<Scalar, Alignment>;

    Vector(size_t size) : size_(size), data_(AlignedAlloc().allocate(size)) {}

    ~Vector()
    {
        AlignedAlloc().deallocate(data_);
    }

private:
    size_t size_;
    Scalar *data_;
};

int main()
{
    // const size_t size = 10; // Not a multiple of 4 (AVX PacketSize)
    // Vector<double> v(size), w(size), u(size);

    using Traits = SimdTraits<double>;
    std::cout << "Packet size: " << Traits::PacketSize << std::endl;

    return 0;
}