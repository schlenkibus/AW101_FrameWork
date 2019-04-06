#pragma once
#include "Oscillator.h"
#include <iostream>

template<class T>
class LowFrequencyOscillator : public Oscillator<T> {
public:
    LowFrequencyOscillator(int hz) : Oscillator<T>() {
    }
    void setFreq(int i) {
        auto percent = Oscillator<T>::m_data.getSize() / i;
        std::cout << "set LFO phaseinc: " << percent << std::endl;
        Oscillator<T>::setInc(percent);
    }
};


