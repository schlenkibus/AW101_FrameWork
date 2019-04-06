#pragma once


class LowPassFilter {
public:
    LowPassFilter(int cutoff);
    void setCutoffFrequency(float freq);
    float filter(float in, int framePos);
protected:
    float m_lastOut;
    int lastFramePos;
    float m_cutoff;
};


