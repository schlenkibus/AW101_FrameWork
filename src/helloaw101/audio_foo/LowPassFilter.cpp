#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(int cutoff) : m_cutoff{0.025} {
    m_lastOut = 0;
    lastFramePos = 0;
}

void LowPassFilter::setCutoffFrequency(float freq) {
    m_cutoff = freq;
}

float LowPassFilter::filter(float in, int framePos) {
    if(framePos != lastFramePos) {
        m_lastOut = m_lastOut - ( m_cutoff * (m_lastOut - in));
        lastFramePos = framePos;
    }
    return m_lastOut;
}


