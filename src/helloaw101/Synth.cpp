#include "Synth.h"
#include <iostream>
#include <cmath>

Synth::Synth() : m_data{this}, m_sequenceThread{} {
    Pa_Initialize();
    Pa_OpenDefaultStream(&m_stream,
                               0,
                               2,
                               paFloat32,
                               22050,
                               500,
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

void Synth::setFrequencyI(float frequency) {
    for(auto& v: m_data.m_voices) {
        v.m_oscI.setFrequency(frequency);
    }
}

void Synth::setOffsetI(int offset) {
    for(auto& v: m_data.m_voices) {
        v.m_oscI.setOffset(offset);
    }
}

void Synth::setFrequencyII(float frequency) {
    for(auto& v: m_data.m_voices) {
        v.m_oscII.setFrequency(frequency);
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
        v.m_filter2.setCutoffFrequency(cutoff);
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

void Synth::setOSCIFeedback(int feedbackPercent) {
    for(auto&v:m_data.m_voices) {
        v.m_feedback.m_oscIFactor = feedbackPercent / 100.f;
    }
}

void Synth::setOSCIIFeedback(int feedbackPercent) {
    for(auto&v:m_data.m_voices) {
        v.m_feedback.m_oscIIFactor = feedbackPercent / 100.f;
    }
}

Synth::Voice *Synth::getVoice(int index) {
    return &m_data.m_voices[index];
}

void Synth::playSequence() {


    while(m_sequenceThread.joinable()) {
        m_sequenceThread.join();
    }

    m_sequenceThread = std::thread([this](){
            m_data.addNoteOn(16);
            m_data.addNoteOn(18);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            m_data.removeNote(16);
            m_data.removeNote(18);
            m_data.addNoteOn(20);
            m_data.addNoteOn(23);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            m_data.removeNote(23);
            m_data.removeNote(20);
            m_data.addNoteOn(30);
            m_data.addNoteOn(15);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            m_data.removeNote(15);
            m_data.removeNote(30);
        });
}

void Synth::setResonance(float resonance) {
    for(auto& v: m_data.m_voices) {
        v.m_filter.setResonancePercent(resonance);
        v.m_filter2.setResonancePercent(resonance);
    }
}

Synth::Voice::Voice(int key) : m_ampEnv{std::chrono::seconds{1}}, m_filter{25, 0}, m_filter2{25, 0} {
    m_key = key;
    m_lfoIFactor = 0.0f;
    m_lfoIIFactor = 0.0f;
}

auto lastgate = false;

float Synth::Voice::doDsp(int posInFrame) {
    auto fbI = m_feedback.m_oscIFactor * m_feedback.m_oscI;
    auto I = m_oscI.get(posInFrame) + fbI;
    m_feedback.m_oscI = I;
    auto fbII = m_feedback.m_oscIIFactor * m_feedback.m_oscII;
    auto II = m_oscII.get(posInFrame) + fbII;
    m_feedback.m_oscII = II;
    I = m_filter.filter(I, posInFrame);
    II = m_filter2.filter(II, posInFrame);
    auto combined = (I + II) * 0.5;
    return m_ampEnv.getAmp(posInFrame) * combined;
}

void Synth::Voice::noteOn() {
    m_gate = true;
    m_ampEnv.noteOn();
    m_oscI.resetPhase();
}

void Synth::Voice::noteOff() {
    //m_ampEnv.noteOff();
    m_gate = false;
}