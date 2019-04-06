#pragma once

#include <algorithm>

template<class T>
class Oscillator {
public:
    Oscillator() : m_data{} {
        m_phaseInc = 1;
        m_phase = 0;
        lastPosInFrame = -1;
    }
    void setInc(int phaseInc) {
        m_phaseInc = phaseInc;
    }
    float get(int posInFrame) {
        if(posInFrame != lastPosInFrame) {
            lastPosInFrame = posInFrame;
            m_phase += m_phaseInc;
            if(m_phase + m_offset >= m_data.getSize()) {
                m_phase = (m_phase) - m_data.getSize();
            }
        }
        return m_data.get(m_phase + m_offset);
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


