#include "Parameter.h"

Parameter::Parameter(AW101Layout *parent, const std::string &name, Parameter::SliderPack s,
                     std::function<void(int)> valueTarget) : Container(parent), m_onValueChange{std::move(valueTarget)} {
    m_name = addChild<Label>(parent, name);
    m_value = addChild<Label>(parent, std::to_string(s.val));
    m_slider = addChild<Slider>(parent, s.val, s.min, s.max, [this](Slider* s) {
       m_value->setText(std::to_string(s->getValue()));
       m_onValueChange(s->getValue());
    });
    m_onValueChange(s.val);
    computeNode();
}
