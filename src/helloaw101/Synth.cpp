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
}

Synth::~Synth() {
    Pa_StopStream(m_stream);
    Pa_Terminate();
}


float Synth::doDsp(float& phase) {
    if(m_data.gate) {
        phase += 0.01f;
        if( phase >= 1.0f ) phase = -1.0f;
        return std::sin(phase * 440 / 44100.f);
    }
    return 0;
}

void Synth::noteOn() {
    m_data.gate = true;
}

void Synth::noteOff() {
    m_data.gate = false;
}
