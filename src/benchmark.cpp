#include "benchmark.hpp"

#include "neon.hpp"
#include "scalar.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <new>
#include <random>

namespace {

using Clock = std::chrono::high_resolution_clock;

int repetitions_for_size(std::size_t n) {
    if (n <= 1'000) {
        return 200;
    }
    if (n <= 10'000) {
        return 100;
    }
    if (n <= 100'000) {
        return 30;
    }
    if (n <= 1'000'000) {
        return 10;
    }
    return 3;
}

template <typename Function>
ExecutionMetrics measure(Function&& fn, const int32_t* data, std::size_t n) {
    const int repeats = repetitions_for_size(n);

    volatile int64_t sink = fn(data, n);
    (void) sink;

    int64_t sum = 0;
    const auto start = Clock::now();

    for (int i = 0; i < repeats; ++i) {
        sum = fn(data, n);
    }

    const auto end = Clock::now();
    const auto elapsed = std::chrono::duration<double, std::milli>(end - start).count();

    return {sum, elapsed / static_cast<double>(repeats)};
}

}  // namespace

void AlignedInt32Buffer::FreeDeleter::operator()(int32_t* ptr) const {
    std::free(ptr);
}

bool AlignedInt32Buffer::resize(std::size_t size) {
    data_.reset();
    size_ = 0;

    if (size == 0) {
        return true;
    }

    void* raw = nullptr;
    const std::size_t bytes = std::max<std::size_t>(16, size * sizeof(int32_t));

    if (posix_memalign(&raw, 16, bytes) != 0 || raw == nullptr) {
        return false;
    }

    data_.reset(static_cast<int32_t*>(raw));
    size_ = size;
    return true;
}

bool fill_random_data(AlignedInt32Buffer& buffer, std::uint32_t seed) {
    if (buffer.size() == 0 || buffer.data() == nullptr) {
        return false;
    }

    std::mt19937 engine(seed);
    std::uniform_int_distribution<int32_t> distribution(-1'000'000, 1'000'000);

    for (std::size_t i = 0; i < buffer.size(); ++i) {
        buffer[i] = distribution(engine);
    }

    return true;
}

ExecutionMetrics benchmark_scalar(const int32_t* data, std::size_t n) {
    return measure(process_array_scalar, data, n);
}

ExecutionMetrics benchmark_neon(const int32_t* data, std::size_t n) {
    return measure(process_array_neon, data, n);
}

std::vector<BenchmarkRow> run_standard_benchmark() {
    const std::vector<std::size_t> sizes = {1'000, 10'000, 100'000, 1'000'000};
    std::vector<BenchmarkRow> rows;
    rows.reserve(sizes.size());

    for (std::size_t i = 0; i < sizes.size(); ++i) {
        AlignedInt32Buffer buffer;
        if (!buffer.resize(sizes[i]) || !fill_random_data(buffer, 100U + static_cast<std::uint32_t>(i))) {
            rows.push_back({sizes[i], 0.0, 0.0, 0.0, 0, 0, false});
            continue;
        }

        const ExecutionMetrics scalar = benchmark_scalar(buffer.data(), buffer.size());
        const ExecutionMetrics neon = benchmark_neon(buffer.data(), buffer.size());

        const double speedup = neon.milliseconds > 0.0
            ? scalar.milliseconds / neon.milliseconds
            : 0.0;

        rows.push_back({
            buffer.size(),
            scalar.milliseconds,
            neon.milliseconds,
            speedup,
            scalar.sum,
            neon.sum,
            scalar.sum == neon.sum
        });
    }

    return rows;
}
