#pragma once
#include <vector>
#include "../HighLevel/Button.h"
#include "OnClickCallbackServer.h"

class LayoutCallbackManager {
public:
    LayoutCallbackManager();
    void addButtonCallback(Button* button);
    void onClickReceived(const UIID &id);
    void updateNode(Control *control);

    void onReleaseReceived(UIID uiid);

protected:
    std::vector<Button*> m_buttons;
    OnClickCallbackServer m_clickServer;
};


