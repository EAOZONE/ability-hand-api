#include <array>
#include <chrono>
#include <cmath>
#include <stdio.h>

#include "wrapper.h"

int main(int argc, char* argv[]) {
    AHWrapper wrapper = AHWrapper(0x50, 1000000);
    wrapper.connect();

    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<double>(now.time_since_epoch());
    std::array<float, 6> cmd = { 30.0, 30.0, 30.0, 30.0, 30.0, -30 };

    for (size_t i = 0; i < 10000; i++) {

        // Calculate Hand Wave
        now = std::chrono::steady_clock::now();
        duration = std::chrono::duration<double>(now.time_since_epoch());
        for (size_t j = 0; j < cmd.size(); ++j) {
            double ft = static_cast<double>(duration.count()) * 3.0 +
                j * (2.0 * 3.14159265359 / 12.0);
            cmd[j] = (0.5 * std::sin(ft) + 0.5) * 45.0 + 15.0;
        }
        cmd[5] = -cmd[5];
        auto t0 = std::chrono::high_resolution_clock::now();
        wrapper.write_once(cmd, POSITION, 0);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        std::printf("write time = %llu \n", (unsigned long long)us);

    }
}