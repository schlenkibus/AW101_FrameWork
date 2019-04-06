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
    auto sum = 0.f;
    for(auto& voice: m_data.m_voices) {
        sum += voice.doDsp(posInFrame);
    }
    return sum / m_data.m_voices.size();
}

void Synth::setIncI(int inc) {
    for(auto& v: m_data.m_voices) {
        v.m_oscI.setInc(inc);
    }
}

void Synth::setOffsetI(int offset) {
    for(auto& v: m_data.m_voices) {
        v.m_oscI.setOffset(offset);
    }
}

void Synth::setIncII(int inc) {
    for(auto& v: m_data.m_voices) {
        v.m_oscII.setInc(inc);
    }
}

void Synth::setOffsetII(int offset) {
    for(auto& v: m_data.m_voices) {
        v.m_oscII.setOffset(offset);
    }
}

void Synth::setCutoffFrequency(float cutoff) {
    for(auto& v: m_data.m_voices) {
        v.m_filter.setCutoffFrequency(cutoff);
    }
}

void Synth::setLFOIncI(int inc) {
    for(auto& v: m_data.m_voices) {
        v.m_lfoI.setInc(inc);
    }
}

void Synth::setLFOIncII(int inc) {
    for(auto& v: m_data.m_voices) {
        v.m_lfoII.setInc(inc);
    }
}


Synth::Voice::Voice(int key) : m_ampEnv{std::chrono::seconds{1}}, m_filter{25} {
    m_key = key;
}

float Synth::Voice::doDsp(int posInFrame) {
    auto I = m_lfoI.get(posInFrame) * m_oscI.get(posInFrame);
    auto II = m_lfoII.get(posInFrame) * m_oscII.get(posInFrame);
    auto combined = I + II;
    return m_ampEnv.getAmp(posInFrame) * m_filter.filter(combined, posInFrame);
}

void Synth::Voice::noteOn() {
    m_ampEnv.noteOn();
}

void Synth::Voice::noteOff() {
    m_ampEnv.noteOff();
}