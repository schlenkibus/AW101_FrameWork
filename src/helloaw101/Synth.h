#pragma once

#include <array>
#include <cmath>
#include <chrono>
#include "portaudio.h"
#include "audio_foo/Oscillator.h"
#include "audio_foo/LowPassFilter.h"
#include "audio_foo/LowFrequencyOscillator.h"

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

    struct paTestData
    {
    public:
        paTestData(Synth* s) : m_ramp{std::chrono::milliseconds(350)}, m_filter{500}, m_lfo{1}, m_lfo2{1} {
            m_synth = s;
        }
        float left_phase = 0;
        float right_phase = 0;
        Synth* m_synth;
        Envelope m_ramp;
        Oscillator<SineWaveTable<15000>> m_I;
        Oscillator<SineWaveTable<15000>> m_II;
        LowPassFilter m_filter;
        LowFrequencyOscillator<SineWaveTable<25000>> m_lfo;
        LowFrequencyOscillator<SineWaveTable<25000>> m_lfo2;
        float factor = 0.5;


        int phaseIncOscI = 1;
        int phaseIncOSCII = 1;
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
    void noteOn();
    void noteOff();
    float doDsp(int posInFrame);
    paTestData m_data;
protected:
    PaStream *m_stream;
};


