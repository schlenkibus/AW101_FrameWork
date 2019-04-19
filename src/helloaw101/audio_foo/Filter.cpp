#include <algorithm>
#include <math.h>
#include "Filter.h"

Filter::Filter(FilterType type, float frequency, float q, float dbGain) : m_type{type} {
    m_frequency = frequency;
    m_q = q;
    m_dbGain = dbGain;

    recalcCoefficents();

    prev_input_1 = 0.0;
    prev_input_2 = 0.0;
    prev_output_1 = 0.0;
    prev_output_2 = 0.0;

    lastFramePos = -1;
}

float Filter::filter(float in, int framePos) {
    if(framePos != lastFramePos) {
        lastFramePos = framePos;
        float output = 	(b0 * in) +
                          (b1 * prev_input_1) +
                          (b2* prev_input_2) -
                          (a1* prev_output_1) -
                (a2* prev_output_2);

        prev_input_2 = prev_input_1;
        prev_input_1 = in;
        prev_output_2 = prev_output_1;
        prev_output_1 = output;
        return output;
    }
    return prev_output_1;
}

void Filter::load_coefficents(float A, float omega, float sn, float cs, float alpha, float beta) {
    switch (m_type){
        case FilterType::LOWPASS:
            b0 = (1.0 - cs) /2.0;
            b1 = 1.0 - cs;
            b2 = (1.0 - cs) /2.0;
            a0 = 1.0 + alpha;
            a1 = -2.0 * cs;
            a2 = 1.0 - alpha;
            break;

        case FilterType::HIGHPASS:
            b0 = (1 + cs) /2.0;
            b1 = -(1 + cs);
            b2 = (1 + cs) /2.0;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;

        case FilterType::BANDPASS:
            b0 = alpha;
            b1 = 0;
            b2 = -alpha;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;

        case FilterType::NOTCH:
            b0 = 1;
            b1 = -2 * cs;
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2 * cs;
            a2 = 1 - alpha;
            break;

        case FilterType::PEAK:
            b0 = 1 + (alpha * A);
            b1 = -2 * cs;
            b2 = 1 - (alpha * A);
            a0 = 1 + (alpha /A);
            a1 = -2 * cs;
            a2 = 1 - (alpha /A);
            break;

        case FilterType::LOWSHELF:
            b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
            b1 = 2 * A * ((A - 1) - (A + 1) * cs);
            b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
            a0 = (A + 1) + (A - 1) * cs + beta * sn;
            a1 = -2 * ((A - 1) + (A + 1) * cs);
            a2 = (A + 1) + (A - 1) * cs - beta * sn;
            break;

        case FilterType::HIGHSHELF:
            b0 = A * ((A + 1) + (A - 1) * cs + beta * sn);
            b1 = -2 * A * ((A - 1) + (A + 1) * cs);
            b2 = A * ((A + 1) + (A - 1) * cs - beta * sn);
            a0 = (A + 1) - (A - 1) * cs + beta * sn;
            a1 = 2 * ((A - 1) - (A + 1) * cs);
            a2 = (A + 1) - (A - 1) * cs - beta * sn;
            break;
    }
}

void Filter::setFrequency(float freq) {
    m_frequency = freq;
    recalcCoefficents();
}

void Filter::setQ(float q) {
    m_q = q;
    recalcCoefficents();
}

void Filter::setdbGain(float gain) {
    m_dbGain = gain;
    recalcCoefficents();
}

void Filter::recalcCoefficents() {
    float A = std::pow(10, m_dbGain / 40); //convert to db
    float omega = 2 * M_PI * m_frequency / 22050;
    float sn = sin(omega);
    float cs = cos(omega);
    float alpha = sn / (2*m_q);
    float beta = sqrt(A + A);
    load_coefficents(A, omega, sn, cs, alpha, beta);
    a1 /= (a0);
    a2 /= (a0);
    b0 /= (a0);
    b1 /= (a0);
    b2 /= (a0);
}


