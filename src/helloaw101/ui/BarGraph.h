#pragma once

#include "../../libaw101/ui/HighLevel/Control.h"
#include "../../libaw101/ui/HighLevel/Container.h"
#include "../../libaw101/ui/Intermediate/JavaScript.h"

class TestModel;
class BarGraph : public Control {
public:
    explicit BarGraph(AW101Layout *parent, TestModel* model);
    void computeNode() override;
    void redraw();
protected:
    TestModel* m_model;
};


