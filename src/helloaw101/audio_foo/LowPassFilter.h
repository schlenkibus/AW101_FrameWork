#pragma once


class LowPassFilter {
public:
    LowPassFilter(int cutoff, float resonance);
    void setCutoffFrequency(float freq);
    void setResonancePercent(float resonance);
    float filter(float in, int framePos);
protected:
    float m_resonance;
    float m_momentum;
    float m_lastOut;
    int lastFramePos;
    float m_cutoff;
    float m_alpha;
};


