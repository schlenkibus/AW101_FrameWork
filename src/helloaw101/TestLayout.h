#pragma once
#include "../libaw101/AW101Layout.h"
#include "TestModel.h"

class Label;
class BarGraph;

class TestLayout : public AW101Layout {
public:
    TestLayout(TestModel* model);
    void loop() override;
protected:
    TestModel* m_model;
    Label* m_audioInfo;
    BarGraph* m_graph;
};


