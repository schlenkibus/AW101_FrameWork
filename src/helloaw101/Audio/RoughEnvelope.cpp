#include <cmath>
#include "RoughEnvelope.h"

RoughEnvelope::RoughEnvelope(RoughEnvelope::ms attackTime, float attack, RoughEnvelope::ms decayTime, float sustain,
                             RoughEnvelope::ms releaseTime) : m_attackTime{attackTime}, m_attack{attack}, m_decayTime{decayTime}, m_sustain{sustain}, m_releaseTime{releaseTime} {

}

void RoughEnvelope::noteOn() {
    m_state = State::Attack;
}

void RoughEnvelope::noteOff() {
    m_state = State::Release;
}

float RoughEnvelope::getValue() {


    switch (m_state) {
        case None:
            return 0;
        case Attack:
            if(m_timer.getElapsed<ms>() >= m_attackTime.count())
                m_state = Decay;
            auto percent = m_attackTime.count() - m_timer.getElapsed<ms>();

            return ramp(0, m_attack, m_timer.getElapsed());
        case Decay:break;
        case Sustain:
            return m_sustain;
        case Release:
            return ramp(0, 1, );
    }
}

float RoughEnvelope::ramp(float f, float f2, int percent) const {
    auto startVal = f;
    auto endVal = f2;
    return (endVal - startVal / 100) * percent + startVal;
}
