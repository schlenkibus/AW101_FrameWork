#pragma once

#include <array>
#include <cmath>
#include "portaudio.h"

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

    typedef struct
    {
        float left_phase = 0;
        float phase = 0;
        float right_phase = 0;
        bool gate = false;
        int freqInHZ = 440;
        Synth* m_synth;
        SineWaveTable<5000> m_sineTable;
        SawWaveTable<3000> m_sawTable;
        bool saw = true;
        int phaseInc = 1;
    } paTestData;


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
            if(data->gate) {
                *out++ = data->m_synth->doDsp(data->left_phase);
                *out++ = data->m_synth->doDsp(data->right_phase);
            } else {
                *out++ = 0;
                *out++ = 0;
            }
        }
        return 0;
    }

    Synth();
    ~Synth();
    void noteOn();
    void noteOff();
    float doDsp(float& phase);

    void incPhaseInc();
    void setPhaseInc(int inc);
    int getPhaseInc();

protected:
    paTestData m_data;
    PaStream *m_stream;
};


