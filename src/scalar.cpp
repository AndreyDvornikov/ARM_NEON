#include "scalar.hpp"

int64_t process_array_scalar(const int32_t* data, std::size_t n) {
    int64_t sum = 0;

    for (std::size_t i = 0; i < n; ++i) {
        const int32_t value = data[i];

        if (value > 0) {
            sum += value;
        } else if (value < 0) {
            sum -= value;
        }
    }

    return sum;
}
