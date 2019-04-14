#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"
#include "../libaw101/ui/HighLevel/ReleaseButton.h"
#include "../libaw101/ui/HighLevel/Slider.h"
#include "ui/Piano.h"
#include "ui/BarGraph.h"
#include "ui/Parameter.h"
#include "ui/PlaytestSequenceButton.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {

    m_root.addChild<Piano>(this, m_model);

    m_parameterStorage = m_root.addChild<CollapseableContainer>(this);

    m_parameterStorage->addChild<Parameter>(this, "OSC I Tune (st)", Parameter::SliderPack{31, 1, 1000, 0.1}, [this](float value) {
        m_model->m_synth.setFrequencyI(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "OSC II Tune (st)", Parameter::SliderPack{12, 1, 1000, 0.1}, [this](float value) {
        m_model->m_synth.setFrequencyII(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "Envelope Attack Time (ms)", Parameter::SliderPack{2, 0, 5000}, [this](int value) {
        m_model->m_synth.setAttack(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "Envelope Release Time (ms)", Parameter::SliderPack{187, 0, 5000}, [this](int value) {
        m_model->m_synth.setRelease(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "Cutoff (?)", Parameter::SliderPack{2500, 0, 5000}, [this](int value) {
        m_model->m_synth.setCutoffFrequency(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "Resonance (%)", Parameter::SliderPack{25, 0, 100}, [this](int value) {
       m_model->m_synth.setResonance(value / 100.f);
    });

    m_parameterStorage->addChild<Parameter>(this, "LFO Tune (st)", Parameter::SliderPack{1, 1, 128}, [this](int value) {
        m_model->m_synth.setLFOIncI(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "LFO Tune (st)", Parameter::SliderPack{1, 1, 128}, [this](int value) {
        m_model->m_synth.setLFOIncII(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "LFO I Factor (%)", Parameter::SliderPack{0, 0, 100}, [this](int value) {
        m_model->m_synth.setLFOIFactor(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "LFO II Factor (%)", Parameter::SliderPack{0, 0, 100}, [this](int value) {
        m_model->m_synth.setLFOIIFactor(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "OSC I Feedback (%)", Parameter::SliderPack{50, 0, 100}, [this](int value) {
        m_model->m_synth.setOSCIFeedback(value);
    });
    m_parameterStorage->addChild<Parameter>(this, "OSC II Feedback (%)", Parameter::SliderPack{60, 0, 100}, [this](int value) {
        m_model->m_synth.setOSCIIFeedback(value);
    });

    m_root.addChild<PlaytestSequenceButton>(this, m_model);
    m_graph = m_root.addChild<BarGraph>(this, m_model);

}

void TestLayout::loop() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    m_graph->redraw();
}
