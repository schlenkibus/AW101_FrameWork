#pragma once
#include <array>

template<size_t count,
        class T,
        typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class RingBuffer {
public:
    RingBuffer() = default;

    T put(T t) {

        if(std::isnan(t)) {
          std::cerr << "NAN Detected!!" << std::endl;
          return {};
        }

        m_data[m_head] = t;
        m_head++;
        if(m_head >= count)
            m_head = 0;
        return t;
    }
    std::array<T, count> m_data;
protected:
    size_t m_head{0};
};