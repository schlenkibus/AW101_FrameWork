#pragma once
#include <chrono>
#include "../../libaw101/ui/backend/tools/Timer.h"

class RoughEnvelope {
    enum State {
        None, Attack, Decay, Sustain, Release
    };
public:
    using ms = std::chrono::milliseconds;
    RoughEnvelope(ms attackTime, float attack, ms decayTime, float sustain, ms releaseTime);
    void noteOn();
    void noteOff();
    float getValue();
protected:
    float ramp(float f, float f2, int percent) const;

    ms m_attackTime;
    float m_attack;
    ms m_decayTime;
    float m_sustain;
    ms m_releaseTime;
    State m_state;
    Timer m_timer;
};


