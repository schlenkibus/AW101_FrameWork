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

void Synth::setAttack(int attackms) {
    for(auto& v: m_data.m_voices) {
        v.m_ampEnv.setAttack(std::chrono::milliseconds{attackms});
    }
}

void Synth::setRelease(int releasems) {
    for(auto&v:m_data.m_voices) {
        v.m_ampEnv.setDecay(std::chrono::milliseconds{releasems});
    }
}

void Synth::setLFOIFactor(int factor) {
    for(auto&v:m_data.m_voices) {
        v.m_lfoIFactor = factor / 100.f;
    }
}

void Synth::setLFOIIFactor(int i) {
    for(auto&v:m_data.m_voices) {
        v.m_lfoIIFactor = i / 100.f;
    }
}


Synth::Voice::Voice(int key) : m_ampEnv{std::chrono::seconds{1}}, m_filter{25} {
    m_key = key;
    m_lfoIFactor = 0.0f;
    m_lfoIIFactor = 0.0f;
}

float Synth::Voice::doDsp(int posInFrame) {
    
    return m_ampEnv.getAmp(posInFrame) * m_oscI.get(posInFrame);
}

void Synth::Voice::noteOn() {
    m_gate = true;
    m_ampEnv.noteOn();
    std::cerr << "note " << m_key << " on\n";
}

void Synth::Voice::noteOff() {
    m_ampEnv.noteOff();
    m_gate = false;
    std::cerr << "note " << m_key << " off\n";
}