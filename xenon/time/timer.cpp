#include "time/timer.hpp"

namespace xenon {
    Timer::Timer() {
        reset();
    }

    void Timer::reset() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    float Timer::get_elapsed() {
        return get_elapsed_millis() * 0.001f;
    }

    float Timer::get_elapsed_millis() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count() * 0.001f * 0.001f;
    }
}