#pragma once
#include "portaudio.h"

class Synth {
public:
    typedef struct
    {
        float left_phase;
        float right_phase;
        bool gate = false;
        int freqInHZ = 440;
        Synth* m_synth;
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
protected:
    paTestData m_data;
    PaStream *m_stream;
};


