#pragma once


#include "Container.h"
#include "Button.h"

class CollapseableContainer : public Container {
public:
    CollapseableContainer(AW101Layout* parent);
    void computeNode() override;

protected:
    class ToggleButton : public Button {
    public:
        ToggleButton(AW101Layout *parent);
        bool isOpen() const;
        void onClick() override;
    protected:
        bool m_open;
    };
    ToggleButton* m_toggleButton;
};


