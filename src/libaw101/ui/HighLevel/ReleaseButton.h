#pragma once
#include "Button.h"

class ReleaseButton : public Button {
public:
    ReleaseButton(AW101Layout *parent);
    virtual void onRelease() = 0;
    void computeNode() override;
};


