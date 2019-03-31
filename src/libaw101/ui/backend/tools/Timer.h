#pragma once
#include <chrono>

class Timer {
public:
    Timer();
    void restart();
    template<class T>
    long getElapsed() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<T>(now - start).count();
    }
protected:
    std::chrono::steady_clock::time_point start;
};


