#pragma once

#include <algorithm>
#include <array>

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

    void resetPhase() {
        m_phase = 0;
    }

    float get(int posInFrame) {
        if(posInFrame != lastPosInFrame) {
            lastPosInFrame = posInFrame;

            float ret = 0.0;

            auto toScan = m_phaseInc + m_offset;
            auto pos = m_phase;
            while(toScan != 0) {

                if(pos >= m_data.getSize())
                    pos = 0;

                ret += m_data.get(pos);

                pos++;
                toScan--;
            }
            m_phase = pos;

            m_cached = ret / (float)(m_phaseInc + m_offset);
        }

        return m_cached;
    }

    void setOffset(int i) {
        m_offset = i;
    }
protected:
    int lastPosInFrame;
    int m_phaseInc;
    int m_phase;
    int m_offset;

    std::array<int, 100> m_incTable;

    float m_cached;
    T m_data;
};


