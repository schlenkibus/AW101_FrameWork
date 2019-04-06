#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"
#include "../libaw101/ui/HighLevel/ReleaseButton.h"
#include "../libaw101/ui/HighLevel/Slider.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {

    m_root.addChild(std::make_unique<ReleaseButton>(this, [this, &model](Button* b){
       m_model->m_synth.noteOn();
    }, [this, &model](Button* b) {
        m_model->m_synth.noteOff();
    }));

    m_root.addChild(std::make_unique<Label>(this, "Phase Inc I"));
    auto phaseIncI = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 500, [this, &model, phaseIncI](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseIncI))->setText(std::to_string(s->getValue()));
        m_model->m_synth.m_data.m_I.setInc(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "Phase Offset I"));
    auto phaseOffI = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 15000, [this, &model, phaseOffI](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseOffI))->setText(std::to_string(s->getValue()));
        m_model->m_synth.m_data.m_I.setOffset(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "Phase Inc II"));
    auto phaseIncII = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 500, [this, &model, phaseIncII](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseIncII))->setText(std::to_string(s->getValue()));
        m_model->m_synth.m_data.m_II.setInc(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "Phase Offset II"));
    auto phaseOffSetII = m_root.addChild(std::make_unique<Label>(this, "0"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 1, 1, 15000, [this, &model, phaseOffSetII](Slider* s) {
        dynamic_cast<Label*>(m_root.getControlById(phaseOffSetII))->setText(std::to_string(s->getValue()));
        m_model->m_synth.m_data.m_II.setOffset(s->getValue());
    }));

    m_root.addChild(std::make_unique<Label>(this, "Lowpass Cutoff"));
    auto cutoffId = m_root.addChild(std::make_unique<Label>(this, "0.025"))->getID().id;
    m_root.addChild(std::make_unique<Slider>(this, 25, 1, 10000, [this, &model, cutoffId](Slider* s) {
        auto label = dynamic_cast<Label*>(m_root.getControlById(cutoffId));
        auto val = s->getValue() / 100000.0;
        label->setText(std::to_string(val));
        m_model->m_synth.m_data.m_filter.setCutoffFrequency(val);
    }));
}

void TestLayout::loop() {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
}
