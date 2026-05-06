#include "neon_core.h"
#include <arm_neon.h>
#include <cstdint>
#include <cstddef>

int64_t process_array_neon(const int32_t* data, size_t n) {
    int64_t sum = 0;
    // Инициализируем векторный аккумулятор нулями [cite: 53]
    int32x4_t acc = vdupq_n_s32(0); 
    
    size_t i = 0;
    // Основной цикл: обрабатываем по 4 элемента за раз [cite: 55]
    for (; i + 3 < n; i += 4) {
        // Вызываем функцию Человека 2 и прибавляем результат к аккумулятору
        int32x4_t res = neon_process_chunk(data + i);
        acc = vaddq_s32(acc, res); 
    }

    // Горизонтальное сложение: схлопываем 4 частичные суммы в одну [cite: 45, 71]
    // Примечание: vaddlvq_s32 доступна на ARMv8-A (64-бит) [cite: 74]
    sum = vaddlvq_s32(acc); 

    // Обработка остатка (хвоста): от 0 до 3 элементов [cite: 72, 73]
    for (; i < n; ++i) {
        int32_t val = data[i];
        if (val > 0) sum += val;
        else if (val < 0) sum -= val; // Модуль для отрицательных [cite: 78, 79]
    }

    return sum;
}