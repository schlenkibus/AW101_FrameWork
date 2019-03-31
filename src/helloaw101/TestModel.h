#pragma once
#include <string>
#include <unordered_map>
#include "../libaw101/ui/backend/tools/Timer.h"
#include "Synth.h"
#include <algorithm>
#include <numeric>

class TestModel {
protected:
    template<size_t count,
            class T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
            >
    struct Average {
        Average() {
            m_data.fill(T{});
            index = 0;
        }
        void put(T t) {
            if(index >= m_data.size())
                index = 0;
            m_data.at(index) = t;
            index++;
        }
        T calculateAverageMS() {
            return std::accumulate(m_data.begin(), m_data.end(), 0) / m_data.size();
        }
        int index;
        std::array<T, count> m_data;
    };
public:
    TestModel() {
        foo = 0;
        str = "nibba";
    }
    int foo;
    std::string str;
    Timer timer;
    Timer loopTime;
    Average<50, long> m_average;
    std::unordered_map<std::string, std::string> generic_storage;
    Synth m_synth;
};


