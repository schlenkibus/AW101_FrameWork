#pragma once
#include <functional>
#include "Control.h"

class AW101Layout;

class Button : public Control {
public:
    Button(AW101Layout* parent);
    virtual void onClick() = 0;
    void computeNode() override;
    const std::string& getButtonText() const;
protected:
    std::string m_buttonText;
};


