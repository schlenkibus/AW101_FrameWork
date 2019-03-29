#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {
    m_root.addChild(std::make_unique<Button>(this, [&](Button* b){
        b->setText("Clicked: " + std::to_string(m_model->foo++));
    }));
}
