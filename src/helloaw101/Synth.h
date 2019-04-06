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
        Envelope(std::chrono::steady_clock::duration rampLength) {
            m_lengthInPhases = rampLength.count() / 44100;
            m_currentPhaseInNote = -1;
        }
        void noteOn() {
            m_currentPhaseInNote = 0;
            release = false;
        }

        void noteOff() {
            m_currentPhaseInNote = m_lengthInPhases;
            release = true;
        }
        float getAmp(int phase) {
            if(m_currentPhaseInNote == -1)
                return 0;

            if(phase != lastPhase) {
                if(release)
                    m_currentPhaseInNote--;
                else
                    m_currentPhaseInNote++;
                lastPhase = phase;
            }


            if(m_currentPhaseInNote == 0 && release) {
                m_currentPhaseInNote = -1;
                release = false;
            }

            if(m_currentPhaseInNote > m_lengthInPhases)
                return 1;

            return (float)m_currentPhaseInNote / (float)m_lengthInPhases;
        }

    protected:
        long m_currentPhaseInNote;
        long m_lengthInPhases;
        int lastPhase = -1;
        bool release = false;
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

protected:
    PaStream *m_stream;
};


