#pragma once

#include <array>
#include <cmath>
#include <chrono>
#include "portaudio.h"
#include "audio_foo/Oscillator.h"
#include "audio_foo/LowPassFilter.h"

class Synth {
public:
    template<int size>
    struct SineWaveTable {
    public:
        SineWaveTable() {
            for(auto i = 0; i < size; i++) {
                m_data[i] = (float) std::sin( ((double)i/(double)size) * M_PI * 2. );
            }
        }
        constexpr const int getSize() const { return size; }
        inline const float get(int i) const { return m_data[i]; }
    protected:
        std::array<float, size> m_data;
    };

    template<int size>
    struct SawWaveTable {
    public:
        SawWaveTable() {
            for(auto i = 0; i < size; i++) {
                m_data[i] = ((1.0f / size) * i);
            }
        }
        constexpr const int getSize() const { return size; }
        inline const float get(int i) const { return m_data[i]; }
    protected:
        std::array<float, size> m_data;
    };

    struct Envelope {
    public:
        enum State {
            None, Attack, Sustain, Decay
        };

        Envelope(std::chrono::steady_clock::duration rampLength) {
            m_state = None;
            setAttack(rampLength);
            setDecay(rampLength);
            m_currentPhaseInNote = -1;
        }
        void setAttack(std::chrono::steady_clock::duration attack) {
            m_attackInPhases = attack.count() / 44100;
        }
        void setDecay(std::chrono::steady_clock::duration decay)  {
            m_decayInPhases = decay.count() / 44100;
        }

        void noteOn() {
            m_currentPhaseInNote = 0;
            m_state = Attack;
        }
        void noteOff() {
            m_state = Decay;
            m_currentPhaseInNote = m_decayInPhases + 1;
        }

        float getAmp(int phase) {
            if(m_state == None)
                return 0;

            if(m_state == Sustain)
                return 1;

            if(phase != lastPhase) {
                switch(m_state) {
                    case Attack:
                        if(m_currentPhaseInNote >= m_attackInPhases)
                            m_state = Sustain;
                        m_currentPhaseInNote++;
                        break;
                    case Decay:
                        if(m_currentPhaseInNote <= 0)
                            m_state = None;
                        m_currentPhaseInNote--;
                        break;
                }
                lastPhase = phase;
            }

            if(m_state == Attack) {
                return (float)m_currentPhaseInNote / (float)m_attackInPhases;
            } else if(m_state == Decay) {
                return (float)m_currentPhaseInNote / (float)m_decayInPhases;
            }
            return 0;
        }
    protected:
        State m_state;
        long m_currentPhaseInNote;
        long m_decayInPhases;
        long m_attackInPhases;
        int lastPhase = -1;
    };

    class Voice {
    public:
        Voice(int key = 0);
        float doDsp(int posInFrame);
        Oscillator<SineWaveTable<10000>> m_oscI;
        Oscillator<SineWaveTable<10000>> m_oscII;
        Oscillator<SineWaveTable<40000>> m_lfoI;
        Oscillator<SineWaveTable<40000>> m_lfoII;
        Envelope m_ampEnv;
        LowPassFilter m_filter;
        int m_key;
        bool m_gate;

        void noteOn();
        void noteOff();
    };

    struct paTestData
    {
        void removeNote(int key) {
            for(auto& v: m_voices) {
                if(v.m_key == key)
                    v.noteOff();
            }
        }

    public:
        paTestData(Synth* s) : m_synth{s} {
        }
        Voice* addNoteOn(int key) {
            bool found = false;
            for(auto& v: m_voices) {
                if(v.m_gate)
                    found = true;
            }
            if(found)
                return nullptr;

            m_voices[nextVoiceIndex].m_key = key;
            m_voices[nextVoiceIndex].m_oscI.setOffset(key);
            m_voices[nextVoiceIndex].m_oscII.setOffset(key);
            auto ret = &m_voices[nextVoiceIndex];
            nextVoiceIndex++;
            if(nextVoiceIndex >= 4)
                nextVoiceIndex = 0;
            ret->noteOn();
            return ret;
        }
        std::array<Voice, 4> m_voices;
        Synth* m_synth;
    protected:
        int nextVoiceIndex = 0;
    };


    static int patestCallback(const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData )
    {
        /* Cast data passed through stream to our structure. */
        auto *data = (paTestData*)userData;
        auto *out = (float*)outputBuffer;
        unsigned int i;
        (void) inputBuffer;

        for( i=0; i<framesPerBuffer; i++ )
        {
            *out++ = data->m_synth->doDsp(i);
            *out++ = data->m_synth->doDsp(i);
        }
        return 0;
    }

    Synth();
    ~Synth();
    float doDsp(int posInFrame);
    paTestData m_data;

    void setIncI(int inc);

    void setOffsetI(int offset);

    void setIncII(int inc);

    void setOffsetII(int offset);

    void setCutoffFrequency(float cutoff);

    void setLFOIncI(int inc);

    void setLFOIncII(int inc);

    void setAttack(int attackms);

    void setRelease(int releasems);

protected:
    PaStream *m_stream;
};


