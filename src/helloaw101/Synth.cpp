#include "Synth.h"
#include <iostream>
#include <cmath>

Synth::Synth() : m_data{this}, m_sequenceThread{} {
    Pa_Initialize();
    Pa_OpenDefaultStream(&m_stream,
                               0,
                               2,
                               paFloat32,
                               48000,
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

void Synth::setOffsetI(float offset) {
    for(auto& v: m_data.m_voices) {
        v.m_oscI.setFrequencyOffset(offset);
    }
}

void Synth::setShaperFold(float fold) {
  for(auto& v: m_data.m_voices) {
    v.m_shaper.setFold(fold);
  }
}

void Synth::setShaperMix(float mix) {
  for(auto& v: m_data.m_voices) {
    v.m_shaper.setWet(mix);
  }
}

Synth::Voice::Voice(int key) {
}

float Synth::Voice::doDsp(int posInFrame) {
    if(!m_gate)
      return 0.0;

    auto osc = m_oscI.get(posInFrame);
    auto shaped = m_shaper.shape(osc);
    return shaped;
}

void Synth::Voice::noteOn(int key) {
    m_gate = true;
    m_key = key;
    m_oscI.setPhaseOffset(keyToFrequency(key));
    m_oscI.resetPhase();
}

void Synth::Voice::noteOff() {
    m_gate = false;
}
float Synth::Voice::keyToFrequency(int key) {
  switch(key) {
  case 0:
    return 261.6;
  case 1:
    return 293.66;
  case 2:
    return 329.63;
  case 3:
    return 349.23;
  case 4:
    return 392;
  case 5:
    return 440;
  case 6:
    return 493.88;
  case 7:
    return 554.37;
  case 8:
    return 622.25;
  case 9:
    return 739.99;
  }
  return 0;
}
