#include "Synth.h"
#include <iostream>
#include <cmath>

Synth::Synth() {
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
    m_data.m_synth = this;
}

Synth::~Synth() {
    Pa_StopStream(m_stream);
    Pa_Terminate();
}


float Synth::doDsp(float& phase) {
    if(m_data.gate) {
        phase += m_data.phaseInc;
        auto sample = 0;

        auto sawPhase = phase;
        if( sawPhase >= m_data.m_sawTable.getSize() )
            sawPhase = phase - m_data.m_sawTable.getSize();
        auto saw = m_data.m_sawTable.get(sawPhase);

        auto sinePhase = phase;
        if( sinePhase >= m_data.m_sineTable.getSize() )
            sinePhase = phase - m_data.m_sineTable.getSize();
        auto sine = m_data.m_sineTable.get(sinePhase);

        if( phase >= m_data.m_sineTable.getSize() && phase >= m_data.m_sawTable.getSize())
            phase = 0;
        return sine + saw;
    }
    return 0;
}

void Synth::noteOn() {
    m_data.gate = true;
}

void Synth::noteOff() {
    m_data.gate = false;
}

void Synth::incPhaseInc() {
    m_data.phaseInc += 1;
    if(m_data.phaseInc >= 200)
        m_data.phaseInc = 1;
}

void Synth::setPhaseInc(int inc) {
    m_data.phaseInc = inc;
}

int Synth::getPhaseInc() {
    return m_data.phaseInc;
}
