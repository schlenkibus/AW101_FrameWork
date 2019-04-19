#pragma once

class Filter {
public:
    enum class FilterType : int {
        LOWPASS 	= 0,
        HIGHPASS 	= 1,
        BANDPASS 	= 2,
        NOTCH		= 3,
        PEAK		= 4,
        LOWSHELF	= 5,
        HIGHSHELF	= 6
    };
    Filter(FilterType type, float frequency, float q, float dbGain);
    void setFrequency(float freq);
    void setQ(float q);
    void setdbGain(float gain);
    float filter(float in, int framePos);
protected:
    float a0;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
    float prev_input_1;
    float prev_input_2;
    float prev_output_1;
    float prev_output_2;
    FilterType m_type;

    int lastFramePos;

    void load_coefficents(float a, float omega, float sn, float cs, float alpha, float beta);

    float m_frequency;
    float m_q;
    float m_dbGain;

    void recalcCoefficents();
};


