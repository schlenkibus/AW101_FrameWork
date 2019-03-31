#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {

    m_root.addChild(std::make_unique<Button>(this, [this, &model](Button* b){
        m_model->foo += 1;
        auto control = m_root.getControlById(m_model->generic_storage["click_label_uiid"]);
        if(auto label = dynamic_cast<Label*>(control))
            label->setText(std::to_string(m_model->foo));
        onChange();
    }));

    auto labelPtr2 = m_root.addChild(std::make_unique<Label>(this, std::to_string(m_model->foo)));
    m_model->generic_storage["click_label_uiid"] = labelPtr2->getID().id;

    auto labelPtr = m_root.addChild(std::make_unique<Label>(this, std::to_string(m_model->foo)));
    m_model->generic_storage["time_label_uiid"] = labelPtr->getID().id;
}

void TestLayout::loop() {
    static long loops = 0;
    m_model->m_average.put(m_model->loopTime.getElapsed<std::chrono::microseconds>());
    if(m_model->timer.getElapsed<std::chrono::milliseconds>() >= 250) {
        auto control = m_root.getControlById(m_model->generic_storage["time_label_uiid"]);
        if(auto label = dynamic_cast<Label*>(control))
            label->setText("Loops since Update: " + std::to_string(loops) + " Average loop time: " + std::to_string(
                    m_model->m_average.calculateAverageMS()) + "microseconds");

        loops = 0;
        m_model->timer.restart();
    } else {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    loops++;
    m_model->loopTime.restart();
}
