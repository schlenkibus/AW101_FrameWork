#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"
#include "../libaw101/ui/HighLevel/ReleaseButton.h"
#include "../libaw101/ui/HighLevel/Slider.h"
#include "ui/Piano.h"
#include "ui/BarGraph.h"
#include "ui/Parameter.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {

    m_root.addChild<Piano>(this, m_model);

    m_root.addChild<Parameter>(this, "OSC I Tune (st)", Parameter::SliderPack{10, 1, 128}, [this](int value) {
        m_model->m_synth.setIncI(value);
    });
    m_root.addChild<Parameter>(this, "OSC II Tune (st)", Parameter::SliderPack{1, 1, 82}, [this](int value) {
        m_model->m_synth.setIncII(value);
    });
    m_root.addChild<Parameter>(this, "Envelope Attack Time (ms)", Parameter::SliderPack{250, 0, 5000}, [this](int value) {
        m_model->m_synth.setAttack(value);
    });
    m_root.addChild<Parameter>(this, "Envelope Release Time (ms)", Parameter::SliderPack{250, 0, 5000}, [this](int value) {
        m_model->m_synth.setRelease(value);
    });
    m_root.addChild<Parameter>(this, "Cutoff (?)", Parameter::SliderPack{2500, 0, 5000}, [this](int value) {
        m_model->m_synth.setCutoffFrequency(value);
    });
    m_root.addChild<Parameter>(this, "LFO Tune (st)", Parameter::SliderPack{1, 1, 128}, [this](int value) {
        m_model->m_synth.setLFOIncI(value);
    });
    m_root.addChild<Parameter>(this, "LFO Tune (st)", Parameter::SliderPack{1, 1, 128}, [this](int value) {
        m_model->m_synth.setLFOIncII(value);
    });
    m_root.addChild<Parameter>(this, "LFO I Factor (%)", Parameter::SliderPack{0, 0, 100}, [this](int value) {
        m_model->m_synth.setLFOIFactor(value);
    });
    m_root.addChild<Parameter>(this, "LFO II Factor (%)", Parameter::SliderPack{0, 0, 100}, [this](int value) {
        m_model->m_synth.setLFOIIFactor(value);
    });
    m_root.addChild<Parameter>(this, "OSC I Feedback (%)", Parameter::SliderPack{1, 0, 100}, [this](int value) {
        m_model->m_synth.setOSCIFeedback(value);
    });
    m_root.addChild<Parameter>(this, "OSC II Feedback (%)", Parameter::SliderPack{1, 0, 100}, [this](int value) {
        m_model->m_synth.setOSCIIFeedback(value);
    });

    m_audioInfo = m_root.addChild<Label>(this, "Audio Info");
    m_graph = m_root.addChild<BarGraph>(this, m_model);

}

void TestLayout::loop() {
    auto str = "Average osc Diff: " + std::to_string(m_model->m_synth.getVoice(0)->m_avgI.calculateAverage());
    m_audioInfo->setText(str);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    m_graph->redraw();
}
