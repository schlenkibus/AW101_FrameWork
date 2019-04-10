#pragma once
#include <array>
#include <algorithm>
#include <numeric>

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
    T calculateAverage() {
        return std::accumulate(m_data.begin(), m_data.end(), 0) / m_data.size();
    }
    int index;
    std::array<T, count> m_data;
};