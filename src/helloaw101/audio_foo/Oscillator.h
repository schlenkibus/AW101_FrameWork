#pragma once

#include <algorithm>
#include <array>
#include <cmath>

template<class T>
class Oscillator {
public:
    Oscillator() : m_data{} {
        m_phaseInc = 1;
        m_phase = 0;
        lastPosInFrame = -1;
        m_phaseOffset = 0;
        calcIncTable();
    }

    void setFrequencyOffset(float frequency) {
      m_frequencyOffset = frequency;
      setFrequency(m_frequency);
    }

    void setFrequency(float frequency) {
        m_frequency = frequency;
        m_phaseInc = m_frequency + m_frequencyOffset * (m_data.getSize() / (float)48000.0f);
    }

    void resetPhase() {
        m_phase = 0;
    }

    float get(int posInFrame) {
        if(posInFrame != lastPosInFrame) {
            lastPosInFrame = posInFrame;
            auto pos = m_phase + m_phaseInc + m_phaseOffset;
            m_cached = m_data.get((int)pos % m_data.getSize());
            if(pos <= m_data.getSize())
                m_phase = pos;
            else
                m_phase = pos - m_data.getSize();
        }
        return m_cached;
    }


    void calcIncTable() {

    }

    void setPhaseOffset(float d) {
        m_phaseOffset = d;
    }

protected:
    float m_frequency;
    float m_frequencyOffset;
    float m_phaseOffset;

    int lastPosInFrame;
    float m_phaseInc;
    float m_phase;

    std::array<int, 100> m_incTable;

    float m_cached;
    T m_data;
};


