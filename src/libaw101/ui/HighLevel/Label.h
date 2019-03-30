#pragma once
#include "Control.h"

class AW101Layout;

class Label : public Control {
public:
    Label(AW101Layout* parent, const std::string& text);
    void computeNode() override;
    void setText(const std::string& text);
protected:
    std::string m_text;
};


