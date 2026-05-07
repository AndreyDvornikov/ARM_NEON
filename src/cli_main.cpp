#include "benchmark.hpp"

#include <iostream>

int main() {
    const auto rows = run_standard_benchmark();

    std::cout << "Size\tScalar ms\tNEON ms\tSpeedup\tScalar Sum\tNEON Sum\tStatus\n";
    for (const auto& row : rows) {
        std::cout << row.size << '\t'
                  << row.scalar_ms << '\t'
                  << row.neon_ms << '\t'
                  << row.speedup << "x\t"
                  << row.scalar_sum << '\t'
                  << row.neon_sum << '\t'
                  << (row.valid ? "OK" : "Mismatch") << '\n';
    }

    return 0;
}
