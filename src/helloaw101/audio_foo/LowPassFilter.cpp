#include <algorithm>
#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(int cutoff, float resonance) : m_cutoff{0.025}, m_resonance{resonance} {
    m_lastOut = 0;
    lastFramePos = 0;
    setCutoffFrequency(cutoff);
}

void LowPassFilter::setCutoffFrequency(float freq) {
    m_cutoff = freq;
    float RC = 1.0/(m_cutoff*2*3.14);
    float dt = 1.0/22050;
    m_alpha = dt/(RC+dt);
}

float LowPassFilter::filter(float in, int framePos) {
    if(framePos != lastFramePos) {
            float distanceToGo = in - m_lastOut;
            m_momentum += distanceToGo * std::min<float>(m_alpha, 1); // Lower / higher number here will lower / raise the cutoff frequency
            m_lastOut += m_momentum + distanceToGo * std::min<float>(m_resonance, 1); // Higher number here (max 1) lessens resonance
    }
    return m_lastOut;
}

void LowPassFilter::setResonancePercent(float resonance) {
    m_resonance = resonance;
}


