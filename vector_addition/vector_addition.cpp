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

    Scalar &operator()(size_t i) { return data_[i]; }
    const Scalar &operator()(size_t i) const { return data_[i]; }

    size_t size() const { return size_; }
    Scalar *data() { return data_; }
    const Scalar *data() const { return data_; }

    template <typename Expr>
    Vector &operator=(const Expr &expr)
    {
        expr.eval(data_);
        return *this;
    }

private:
    size_t size_;
    Scalar *data_;
};

// Expression template for vector addition
template <typename Lhs, typename Rhs>
class VectorSum
{
public:
    VectorSum(const Lhs &lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

    size_t size() const
    {
        return lhs_.size();
    }

    // SIMD evaluation
    void eval(double *result) const
    {
        using Traits = SimdTraits<double>;
        using Packet = Traits::Packet;
        constexpr size_t PacketSize = Traits::PacketSize;

        size_t i = 0;
        // Process elements in chunks of PacketSize
        for (; i + PacketSize <= size(); i += PacketSize)
        {
            Packet a = Traits::load(&lhs_(i)); // Load packet
            Packet b = Traits::load(&rhs_(i)); // Load packet
            Packet c = Traits::add(a, b);      // Add packets
            Traits::store(&result[i], c);      // Store packet
        }

        // Process remaining elements
        for (; i < size(); ++i)
        {
            result[i] = lhs_(i) + rhs_(i);
        }
    }

private:
    const Lhs &lhs_;
    const Rhs &rhs_;
};

// Overload the + Operator
template <typename Lhs, typename Rhs>
VectorSum<Lhs, Rhs> operator+(const Lhs &lhs, const Rhs &rhs)
{
    return VectorSum<Lhs, Rhs>(lhs, rhs);
}

int main()
{
    const size_t size = 10; // Not a multiple of 4 (AVX PacketSize)
    Vector<double> v(size), w(size), u(size);

    // Initialize vectors
    for (size_t i = 0; i < size; ++i)
    {
        v(i) = static_cast<double>(i);
        w(i) = static_cast<double>(i * 2);
    }

    // Perform vector addition
    u = v + w;

    // Print the result
    std::cout << "u = v + w = ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << u(i) << " ";
    }
    std::cout << std::endl;

    using Traits = SimdTraits<double>;
    std::cout << "Packet size: " << Traits::PacketSize << std::endl;

    return 0;
}