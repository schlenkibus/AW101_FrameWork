#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"
#include "../libaw101/ui/HighLevel/ReleaseButton.h"
#include "../libaw101/ui/HighLevel/Slider.h"
#include "ui/Piano.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {

    m_root.addChild(std::make_unique<Piano>(this, m_model));


    m_root.addChild(std::make_unique<Label>(this, "OSC I Tune"));
    auto phaseIncI = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 500, [this, &model, phaseIncI](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseIncI))->setText(std::to_string(s->getValue()));
        m_model->m_synth.setIncI(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "OSC II Tune"));
    auto phaseIncII = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 500, [this, &model, phaseIncII](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseIncII))->setText(std::to_string(s->getValue()));
        m_model->m_synth.setIncII(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "Lowpass Cutoff"));
    auto cutoffId = m_root.addChild(std::make_unique<Label>(this, "0.025"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 25, 1, 10000, [this, &model, cutoffId](Slider* s) {
        auto label = dynamic_cast<Label*>(m_root.getControlById(cutoffId));
        auto val = s->getValue() / 100000.0f;
        label->setText(std::to_string(val));
        m_model->m_synth.setCutoffFrequency(val);
    }));

    m_root.addChild(std::make_unique<Label>(this, "LFO I Phase Inc"));
    auto lfoID = m_root.addChild(std::make_unique<Label>(this, "1"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 1000, [this, &model, lfoID](Slider* s) {
        auto label = dynamic_cast<Label*>(m_root.getControlById(lfoID));
        auto val = s->getValue();
        label->setText(std::to_string(val));
        m_model->m_synth.setLFOIncI(val);
    }));

    m_root.addChild(std::make_unique<Label>(this, "LFO II Phase Inc"));
    auto lfoID2 = m_root.addChild(std::make_unique<Label>(this, "1"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 1000, [this, &model, lfoID2](Slider* s) {
        auto label = dynamic_cast<Label*>(m_root.getControlById(lfoID2));
        auto val = s->getValue();
        label->setText(std::to_string(val));
        m_model->m_synth.setLFOIncII(val);
    }));
}

void TestLayout::loop() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
}
