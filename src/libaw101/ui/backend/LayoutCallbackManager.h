#pragma once
#include <vector>
#include "../HighLevel/Button.h"
#include "OnClickCallbackServer.h"
#include "KeyEventTarget.h"

class Slider;

class LayoutCallbackManager {
public:
    LayoutCallbackManager();
    void addButtonCallback(Button* button);
    void addSlider(Slider* slider);
    void addKeyEventTarget(KeyEventTarget* target);
    void onClickReceived(const UIID &id);
    void onValueChanged(const UIID &id, float value);
    void updateNode(Control *control);

    void onReleaseReceived(UIID uiid);

    void onKeyDown(std::string key);
    void onKeyUp(std::string key);

    void eval(const std::string javascript);

protected:
    std::vector<Button*> m_buttons;
    std::vector<Slider*> m_sliders;
    std::vector<KeyEventTarget*> m_keyEventTargets;
    OnClickCallbackServer m_clickServer;
};


