#include <iostream>
#include <cstdlib>
#include <cstdint>

int main()
{
    const int alignment = 32;

    // Allocate memory (aligned or unaligned)
    void *ptr = std::malloc(100 * alignment);
    void *alignedPtr = std::aligned_alloc(alignment, 100 * alignment);

    // Check alignment
    bool isPtrAligned = (reinterpret_cast<uintptr_t>(ptr) % alignment == 0);
    bool isAlignedPtrAligned = (reinterpret_cast<uintptr_t>(alignedPtr) % alignment == 0);

    // Print results
    std::cout << "ptr is aligned: " << isPtrAligned << std::endl;
    std::cout << "alignedPtr is aligned: " << isAlignedPtrAligned << std::endl;

    std::free(ptr);
    std::free(alignedPtr);
}