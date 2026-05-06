#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include "scalar.h"
#include "neon_core.h"

// Объявляем твою функцию-обертку
int64_t process_array_neon(const int32_t* data, size_t n);

int main() {
    const size_t N = 1000000; // 1 миллион элементов для точности замера
    
    // Используем alignas(16) для эффективной загрузки данных в NEON [cite: 41, 89]
    alignas(16) std::vector<int32_t> data(N);
    
    // Заполняем массив случайными данными
    for (size_t i = 0; i < N; ++i) {
        data[i] = (rand() % 2000) - 1000; // Числа от -1000 до 999
    }

    // --- Тест Скалярной версии ---
    auto start_s = std::chrono::high_resolution_clock::now();
    int64_t res_scalar = process_array_scalar(data.data(), N);
    auto end_s = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_s = end_s - start_s;

    // --- Тест NEON версии ---
    auto start_n = std::chrono::high_resolution_clock::now();
    int64_t res_neon = process_array_neon(data.data(), N);
    auto end_n = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_n = end_n - start_n;

    // Проверка корректности (Валидация)
    std::cout << "Scalar Result: " << res_scalar << "\n";
    std::cout << "NEON Result:   " << res_neon << "\n";
    
    if (res_scalar == res_neon) {
        std::cout << "Validation: SUCCESS\n";
    } else {
        std::cerr << "Validation: FAILED!\n";
        return 1;
    }

    // Отчет о производительности
    std::cout << "Scalar Time: " << elapsed_s.count() << " ms\n";
    std::cout << "NEON Time:   " << elapsed_n.count() << " ms\n";
    std::cout << "Speedup:     " << (elapsed_s.count() / elapsed_n.count()) << "x\n";

    return 0;
}