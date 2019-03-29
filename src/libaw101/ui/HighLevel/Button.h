#pragma once
#include <functional>
#include "Control.h"

class AW101Layout;

class Button : public Control {
public:
    typedef std::function<void(Button*)> tButtonCallback;
    Button(AW101Layout* parent, tButtonCallback callback);

    virtual void onClick();

    CTML::Node getNode() const override;
protected:
    tButtonCallback m_callback;
};


