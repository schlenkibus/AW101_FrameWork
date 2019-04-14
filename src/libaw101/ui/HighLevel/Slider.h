#pragma once
#include "Control.h"
#include "../../AW101Layout.h"

class Slider : public Control {
public:
    typedef std::function<void(Slider*)> tValueChangedCallback;
    explicit Slider(AW101Layout *parent, int value, int min, int max, tValueChangedCallback cb) : Control(parent), m_changedCB{std::move(cb)} {
        parent->getCallbackManager()->addSlider(this);
        m_value = value;
        m_min = min;
        m_max = max;
    }

    void onValueChanged(float value) {
        m_value = value;
        m_changedCB(this);
    }

    void computeNode() override {
        clear();
        m_node.SetName("input.Slider#"+m_id.id);
        m_node.SetAttribute("type", "range");
        m_node.SetAttribute("max", std::to_string(m_max));
        m_node.SetAttribute("min", std::to_string(m_min));
        m_node.SetAttribute("oninput", "valuechange(this.id, this.value);");
        m_node.SetAttribute("value", std::to_string(m_value));
        m_node.SetAttribute("step", std::to_string(m_step));
    }

    void setStepSize(float stepSize) {
        m_step = stepSize;
    }

    float getValue() {
        return m_value;
    }

protected:
    tValueChangedCallback m_changedCB;
    float m_value;
    int m_min;
    int m_max;
    float m_step;
};


