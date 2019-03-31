#include "Timer.h"

Timer::Timer() {
    restart();
}

void Timer::restart() {
    start = std::chrono::steady_clock::now();
}
