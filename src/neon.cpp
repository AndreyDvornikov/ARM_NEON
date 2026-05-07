#include "neon.hpp"

#include <cstddef>
#include <cstdint>

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
namespace {

inline int32x4_t compute_contribution(int32x4_t vec) {
    const int32x4_t zero = vdupq_n_s32(0);

    // Compare against zero to build masks instead of branching.
    const uint32x4_t mask_pos = vcgtq_s32(vec, zero);
    const uint32x4_t mask_neg = vcltq_s32(vec, zero);

    // Branchless absolute value:
    // sign = 0 for positive values, -1 for negative values.
    // The arithmetic shift is the SIMD equivalent of using the barrel shifter.
    const int32x4_t sign = vshrq_n_s32(vec, 31);
    int32x4_t abs_val = veorq_s32(vec, sign);
    abs_val = vsubq_s32(abs_val, sign);

    const int32x4_t pos_part = vandq_s32(vec, vreinterpretq_s32_u32(mask_pos));
    const int32x4_t neg_part = vandq_s32(abs_val, vreinterpretq_s32_u32(mask_neg));

    return vorrq_s32(pos_part, neg_part);
}

}  // namespace
#endif

int64_t process_array_neon(const int32_t* data, std::size_t n) {
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
    int32x4_t acc0 = vdupq_n_s32(0);
    int32x4_t acc1 = vdupq_n_s32(0);
    std::size_t i = 0;

    // Process 8 elements per iteration:
    // two loads, two independent accumulators, and an explicit prefetch.
    for (; i + 7 < n; i += 8) {
        __builtin_prefetch(data + i + 32, 0, 1);

        const int32x4_t vec0 = vld1q_s32(data + i);
        const int32x4_t vec1 = vld1q_s32(data + i + 4);

        acc0 = vaddq_s32(acc0, compute_contribution(vec0));
        acc1 = vaddq_s32(acc1, compute_contribution(vec1));
    }

    int32x4_t acc = vaddq_s32(acc0, acc1);
    int64_t sum = 0;

#if defined(__aarch64__)
    sum += static_cast<int64_t>(vaddvq_s32(acc));
#else
    int32x2_t partial = vadd_s32(vget_low_s32(acc), vget_high_s32(acc));
    partial = vpadd_s32(partial, partial);
    sum += static_cast<int64_t>(vget_lane_s32(partial, 0));
#endif

    for (; i < n; ++i) {
        const int32_t value = data[i];

        if (value > 0) {
            sum += value;
        } else if (value < 0) {
            sum += fast_abs_asm(value);
        }
    }

    return sum;
#else
    int64_t sum = 0;
    for (std::size_t i = 0; i < n; ++i) {
        const int32_t value = data[i];
        if (value > 0) {
            sum += value;
        } else if (value < 0) {
            sum += fast_abs_asm(value);
        }
    }
    return sum;
#endif
}
