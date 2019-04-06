#pragma once

#include <algorithm>

template<class T>
class Oscillator {
public:
    Oscillator() : m_data{} {
        m_phaseInc = 1;
        m_phase = 0;
        lastPosInFrame = -1;
        m_offset = 0;
    }
    void setInc(int phaseInc) {
        m_phaseInc = phaseInc;
    }
    float get(int posInFrame) {
        if(posInFrame != lastPosInFrame) {
            lastPosInFrame = posInFrame;
            m_phase += m_phaseInc + m_offset;
            if(m_phase >= m_data.getSize()) {
                m_phase = 0;
            }
        }
        return m_data.get(m_phase);
    }

    void setOffset(int i) {
        m_offset = i;
    }
protected:
    int lastPosInFrame;
    int m_phaseInc;
    int m_phase;
    int m_offset;
    T m_data;
};


