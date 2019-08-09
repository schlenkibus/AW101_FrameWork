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

    m_parameterStorage->addChild<Parameter>(this, "OSC I PhaseOffset", Parameter::SliderPack{0, -300, 300, 0.1}, [this](float value) {
        m_model->m_synth.setOffsetI(value);
    });

    m_parameterStorage->addChild<Parameter>(this, "Shaper Fold", Parameter::SliderPack{0, 0, 1, 0.01}, [this](float v) {
      m_model->m_synth.setShaperFold(v);
    });

    m_parameterStorage->addChild<Parameter>(this, "Shaper Mix", Parameter::SliderPack{0, 0, 1, 0.01}, [this](float value) {
      m_model->m_synth.setShaperMix(value);
    });


  m_graph = m_root.addChild<BarGraph>(this, m_model);

}

void TestLayout::loop() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    m_graph->redraw();
}
