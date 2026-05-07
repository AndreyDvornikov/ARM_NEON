#pragma once

#include <cstddef>
#include <cstdint>

// Demonstrates the ARM barrel shifter trick:
// sign = x >> 31, then (x ^ sign) - sign computes abs(x) without branches.
inline int32_t fast_abs_asm(int32_t x) {
#if defined(__arm__) || defined(__aarch64__) || defined(ARM_NEON_TARGET)
    int32_t result = 0;
    int32_t sign = 0;

#if defined(__aarch64__)
    __asm__ volatile(
        "asr %w[sign], %w[input], #31\n\t"
        "eor %w[result], %w[input], %w[sign]\n\t"
        "sub %w[result], %w[result], %w[sign]\n\t"
        : [result] "=&r" (result), [sign] "=&r" (sign)
        : [input] "r" (x)
        : "cc");
#else
    __asm__ volatile(
        "asr %[sign], %[input], #31\n\t"
        "eor %[result], %[input], %[sign]\n\t"
        "sub %[result], %[result], %[sign]\n\t"
        : [result] "=&r" (result), [sign] "=&r" (sign)
        : [input] "r" (x)
        : "cc");
#endif

    return result;
#else
    const int32_t sign = x >> 31;
    return (x ^ sign) - sign;
#endif
}

int64_t process_array_neon(const int32_t* data, std::size_t n);
