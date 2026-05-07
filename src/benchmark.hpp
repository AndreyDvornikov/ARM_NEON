#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

struct ExecutionMetrics {
    int64_t sum = 0;
    double milliseconds = 0.0;
};

struct BenchmarkRow {
    std::size_t size = 0;
    double scalar_ms = 0.0;
    double neon_ms = 0.0;
    double speedup = 0.0;
    int64_t scalar_sum = 0;
    int64_t neon_sum = 0;
    bool valid = false;
};

class AlignedInt32Buffer {
public:
    bool resize(std::size_t size);

    int32_t* data() { return data_.get(); }
    const int32_t* data() const { return data_.get(); }
    std::size_t size() const { return size_; }

    int32_t& operator[](std::size_t index) { return data_.get()[index]; }
    const int32_t& operator[](std::size_t index) const { return data_.get()[index]; }

private:
    struct FreeDeleter {
        void operator()(int32_t* ptr) const;
    };

    std::unique_ptr<int32_t, FreeDeleter> data_;
    std::size_t size_ = 0;
};

bool fill_random_data(AlignedInt32Buffer& buffer, std::uint32_t seed = 42U);
ExecutionMetrics benchmark_scalar(const int32_t* data, std::size_t n);
ExecutionMetrics benchmark_neon(const int32_t* data, std::size_t n);
std::vector<BenchmarkRow> run_standard_benchmark();
