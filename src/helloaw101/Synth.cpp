#include "Synth.h"

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
    Pa_Sleep(3000);
}

Synth::~Synth() {
    Pa_StopStream(m_stream);
    Pa_Terminate();
}

float Synth::calcSample(float phase) {
    ;
}
