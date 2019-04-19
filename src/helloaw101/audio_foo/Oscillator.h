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
        m_offset = 0;
        m_phaseOffset = 0;
        calcIncTable();
    }

    void setFrequency(float frequency) {
        m_frequency = frequency;
        m_phaseInc = m_frequency * (m_data.getSize() / (float)22050.0f); //22050 / size
    }

    void setInc(int phaseInc) {
        m_phaseInc = phaseInc;
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

    void setOffset(int i) {
        m_offset = i;
    }

    void calcIncTable() {

    }

    void setPhaseOffset(float d) {
        m_phaseOffset = d;
    }

protected:
    float m_frequency;
    float m_phaseOffset;

    int lastPosInFrame;
    int m_phaseInc;
    int m_phase;
    int m_offset;

    std::array<int, 100> m_incTable;

    float m_cached;
    T m_data;
};


