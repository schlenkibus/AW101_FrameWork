#pragma once
#include "Button.h"

class ReleaseButton : public Button {
public:
    ReleaseButton(AW101Layout *parent, tButtonCallback downCB, tButtonCallback upCB);
    virtual void onRelease();

    void computeNode() override;

protected:
    tButtonCallback m_reaseCallback;
};


