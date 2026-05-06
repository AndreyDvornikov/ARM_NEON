#include <arm_neon.h>
#include <cstdint>

int32x4_t neon_process_chunk(const int32_t* data) {
    int32x4_t vec = vld1q_s32(data);

    int32x4_t zero = vdupq_n_s32(0);

    uint32x4_t mask_pos = vcgtq_s32(vec, zero);
    uint32x4_t mask_neg = vcltq_s32(vec, zero);

    int32x4_t sign = vshrq_n_s32(vec, 31);

    int32x4_t abs_vec = veorq_s32(vec, sign);
    abs_vec = vsubq_s32(abs_vec, sign);

    int32x4_t pos_part =
        vandq_s32(vec, vreinterpretq_s32_u32(mask_pos));

    int32x4_t neg_part =
        vandq_s32(abs_vec, vreinterpretq_s32_u32(mask_neg));

    int32x4_t result = vorrq_s32(pos_part, neg_part);

    return result;
}