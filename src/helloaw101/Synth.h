#pragma once

#include <array>
#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include "portaudio.h"
#include "audio_foo/Oscillator.h"
#include "audio_foo/Filter.h"
#include "foo/Average.h"
#include "foo/RingBuffer.h"

class Synth {
public:
    template<int size>
    struct SineWaveTable {
    public:
        SineWaveTable() {
            double angle = 0.0;
            for (int i = 0; i < size; i++)
            {
                m_data[i] = float(std::sin(angle));
                angle += (2 * M_PI) / size;
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
            m_attackInPhases = attack.count() / 22050;
        }
        void setDecay(std::chrono::steady_clock::duration decay)  {
            m_decayInPhases = decay.count() / 22050;
        }

        void noteOn() {
            if(m_state == None) {
                m_currentPhaseInNote = 0;
            }
            m_state = Attack;
        }
        void noteOff() {
            if(m_state == Sustain) {
                m_currentPhaseInNote = m_decayInPhases;
            }
            m_state = Decay;

        }

        float getAmp(int phase) {
            if(phase != lastPhase) {
                switch(m_state) {
                    case Attack:
                        if(m_currentPhaseInNote >= m_attackInPhases) {
                            m_state = Decay;
                            m_currentPhaseInNote = m_decayInPhases;
                        }
                        else
                            m_currentPhaseInNote++;
                        break;
                    case Decay:
                        if(m_currentPhaseInNote <= 0)
                            m_state = None;
                        else
                            m_currentPhaseInNote--;
                        break;
                    case None:
                        return 0;
                    case Sustain:
                        return 1;
                }
                lastPhase = phase;
            }

            switch(m_state) {
                case Attack:
                    return std::min((float)m_currentPhaseInNote / (float)m_attackInPhases, 1.0f);
                case Decay:
                    return std::min((float)m_currentPhaseInNote / (float)m_decayInPhases, 1.0f);
                case Sustain:
                    return 1;
                case None:
                    return 0;
            }
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
        Oscillator<SineWaveTable<8192>> m_oscI;
        Oscillator<SineWaveTable<8192>> m_oscII;
        Oscillator<SineWaveTable<8192>> m_lfoI;
        Oscillator<SineWaveTable<131072>> m_lfoII;
        Average<2000, float> m_avgI;
        Envelope m_ampEnv;
        Filter m_filter;
        Filter m_filter2;
        int m_key;
        bool m_gate;
        float m_lfoIFactor;
        float m_lfoIIFactor;
        void noteOn();
        void noteOff();

        struct FeedBack {
            float m_oscI = 0.0f;
            float m_oscII = 0.0f;
            float m_oscIFactor = 0.0f;
            float m_oscIIFactor = 0.0f;
        };

        FeedBack m_feedback;
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
        bool hasNoteForKey(int key) {
            for(auto& v: m_voices) {
                if(key == v.m_key && v.m_gate )
                    return true;
            }
            return false;
        }
        Voice* addNoteOn(int key) {
            m_voices[nextVoiceIndex].m_key = key;
            m_voices[nextVoiceIndex].m_oscI.setOffset(key);
            m_voices[nextVoiceIndex].m_oscII.setOffset(key);
            auto ret = &m_voices[nextVoiceIndex];
            nextVoiceIndex++;
            if(nextVoiceIndex >= m_voices.size()) {
                nextVoiceIndex = 0;
            }
            ret->noteOn();
            return ret;
        }
        std::array<Voice, 4> m_voices;
        Synth* m_synth;
        RingBuffer<5000, float> m_samples;
        Average<200, float> m_avgFrameLength;
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
            *out++ = data->m_samples.put(data->m_synth->doDsp(i));
            *out++ = data->m_synth->doDsp(i);
        }
        return 0;
    }

    Synth();
    ~Synth();
    float doDsp(int posInFrame);
    paTestData m_data;

    void setFrequencyI(float frequency);
    void setOffsetI(int offset);
    void setFrequencyII(float frequency);
    void setOffsetII(int offset);
    void setCutoffFrequency(float cutoff);
    void setLFOIncI(int inc);
    void setLFOIncII(int inc);
    void setAttack(int attackms);
    void setRelease(int releasems);
    void setLFOIFactor(int factor);
    void setLFOIIFactor(int i);
    void setOSCIFeedback(int feedbackPercent);
    void setOSCIIFeedback(int feedbackPercent);
    Voice* getVoice(int index);

    void playSequence();

    void setResonance(float resonance);

    void setQ(float i);

    void setDBGain(float db);

    void setPhaseOffsetI(float phaseOffset);

protected:
    std::thread m_sequenceThread;
    PaStream *m_stream;
};


