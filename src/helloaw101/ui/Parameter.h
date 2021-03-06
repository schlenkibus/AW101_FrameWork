#pragma once
#include "../../libaw101/ui/HighLevel/Container.h"
#include "../../libaw101/ui/HighLevel/Label.h"
#include "../../libaw101/ui/HighLevel/Slider.h"

class Parameter : public Container {
public:
    struct SliderPack {
        float val;
        float min;
        float max;
        float step = 1;
    };

    Parameter(AW101Layout *parent, const std::string& name, SliderPack s, std::function<void(float)> valueTarget);
protected:
    Label* m_name;
    Label* m_value;
    Slider* m_slider;
    std::function<void(float)> m_onValueChange;
};


