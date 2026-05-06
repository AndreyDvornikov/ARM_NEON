#ifndef NEON_CORE_H
#define NEON_CORE_H
#include <arm_neon.h>
#include <cstdint>

int32x4_t neon_process_chunk(const int32_t* data);

#endif