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

    float calcSample(float phase);

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
            *out++ = data->m_synth->dsp(data->left_phase);  /* left */
            *out++ = data->m_synth->dsp(data->right_phase);  /* right */
            /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
            data->left_phase += 0.01f;
            /* When signal reaches top, drop back down. */
            if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
            /* higher pitch so we can distinguish left and right. */
            data->right_phase += 0.03f;
            if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
        }
        return 0;
    }

    Synth();
    ~Synth();
protected:
    paTestData m_data;
    PaStream *m_stream;
};


