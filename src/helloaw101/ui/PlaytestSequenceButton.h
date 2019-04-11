#pragma once
#include "../../libaw101/ui/HighLevel/Button.h"
#include "../TestModel.h"

class PlaytestSequenceButton : public Button {
public:
    PlaytestSequenceButton(AW101Layout* parent, TestModel* model);

    void onClick() override;
protected:
    TestModel* m_model;
};


