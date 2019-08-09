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
#include <functional>


class Synth {
public:
    template<int size>
    struct SineWaveTable {
    public:
        SineWaveTable() {
          auto phaseInc = 1 * M_2_PI / 48000;

          for(int i=0;i<=size;i++)
          {
            constexpr double rads = M_PI/180.0;
            constexpr double step = 360.0 / size;
            m_data[i] = std::sin(step*i*rads);
          }
        }
        constexpr const int getSize() const { return size; }
        inline const float get(int i) const { return m_data[i]; }
    protected:
        std::array<float, size> m_data;
    };

    class Shaper {
    public:
      float shape(float in) {
        auto ret = in;
        if(std::isnan(ret))
          return in;
        return ret;
      }

      void setWet(float mix) {
        m_wetMix = mix;
      }

      void setParameter(int index, float w) {
        m_params[index] = w;
      }

      void setFold(float fold) {

      }

      float getWet() {
        return m_wetMix = 0.0;
      }

    protected:
      std::unordered_map<float, float> m_params;

      float m_wetMix = 1.0f;
    };

    class Voice {
    public:
        Voice(int key = 0);
        float doDsp(int posInFrame);
        Oscillator<SineWaveTable<96000>> m_oscI;
        Shaper m_shaper;

        void noteOn(int key);
        void noteOff();

        float keyToFrequency(int key);

        bool m_gate{};
        int m_key = 0;
    };

    struct paTestData
    {

    public:
        paTestData(Synth* s) : m_synth{s} {
        }

        void addNoteOn(int key) {
            for(auto& v: m_voices) {
              if(!v.m_gate) {
                v.noteOn(key);
                break;
              }
            }
        }

        void removeNote(int key) {
          for(auto& v: m_voices) {
            if(v.m_key == key)
              v.noteOff();
          }
        }

        std::array<Voice, 4> m_voices;
        Synth* m_synth;
        RingBuffer<5000, float> m_samples;
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
    void setOffsetI(float offset);
    void setShaperMix(float mix);
    void setShaperFold(float fold);



protected:
    std::thread m_sequenceThread;
    PaStream *m_stream;
};


