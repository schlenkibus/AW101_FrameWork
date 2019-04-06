#pragma once
#include <vector>
#include "../HighLevel/Button.h"
#include "OnClickCallbackServer.h"

class Slider;

class LayoutCallbackManager {
public:
    LayoutCallbackManager();
    void addButtonCallback(Button* button);
    void addSlider(Slider* slider);
    void onClickReceived(const UIID &id);
    void onValueChanged(const UIID& id, int value);
    void updateNode(Control *control);

    void onReleaseReceived(UIID uiid);

protected:
    std::vector<Button*> m_buttons;
    std::vector<Slider*> m_sliders;
    OnClickCallbackServer m_clickServer;
};


