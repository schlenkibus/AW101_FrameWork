#include "Synth.h"
#include <iostream>
#include <cmath>

Synth::Synth() : m_data{this} {
    Pa_Initialize();
    Pa_OpenDefaultStream(&m_stream,
                               0,
                               2,
                               paFloat32,
                               44100,
                               paFramesPerBufferUnspecified,
                               patestCallback,
                               &m_data);
    Pa_StartStream(m_stream);
}

Synth::~Synth() {
    Pa_StopStream(m_stream);
    Pa_Terminate();
}


float Synth::doDsp(int posInFrame) {
    auto I = m_data.m_I.get(posInFrame);
    auto II = m_data.m_II.get(posInFrame);
    auto combined = (m_data.factor * I + (1 - m_data.factor) * II);
    return m_data.m_ramp.getAmp(posInFrame) * m_data.m_filter.filter(combined, posInFrame);
}

void Synth::noteOn() {
    m_data.m_ramp.noteOn();
}

void Synth::noteOff() {
    m_data.m_ramp.noteOff();
}
