#include "TestLayout.h"
#include "../libaw101/ui/HighLevel/Button.h"
#include "../libaw101/ui/HighLevel/Label.h"

TestLayout::TestLayout(TestModel *model) : m_model{model} {
    m_root.addChild(std::make_unique<Button>(this, [&](Button* b){
        model->foo += 1;
        for(auto& child: m_root.getChildren()) {
            if(auto label = dynamic_cast<Label*>(child.get()))
                label->setText(std::to_string(model->foo));
        }
    }));
    m_root.addChild(std::make_unique<Label>(this, std::to_string(model->foo)));
}
