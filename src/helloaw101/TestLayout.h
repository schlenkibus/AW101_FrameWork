#pragma once
#include "../libaw101/AW101Layout.h"
#include "TestModel.h"
#include "../libaw101/ui/HighLevel/CollapseableContainer.h"

class Label;
class BarGraph;

class TestLayout : public AW101Layout {
public:
    TestLayout(TestModel* model);
    void loop() override;
protected:
    TestModel* m_model;
    CollapseableContainer* m_parameterStorage;
    BarGraph* m_graph;
};


