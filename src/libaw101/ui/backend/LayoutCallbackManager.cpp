#include "LayoutCallbackManager.h"
#include "PortBroker.h"
#include "../HighLevel/ReleaseButton.h"

LayoutCallbackManager::LayoutCallbackManager() : m_clickServer{this} {

}

void LayoutCallbackManager::addButtonCallback(Button *button) {
    m_buttons.emplace_back(button);
}

void LayoutCallbackManager::onClickReceived(const UIID &id) {
    for(auto& b: m_buttons) {
        if(b->getID().id == id.id) {
            b->onClick();
        }
    }
}

void LayoutCallbackManager::onReleaseReceived(UIID uiid) {
    for(auto& b: m_buttons) {
        if(auto releaseButton = dynamic_cast<ReleaseButton*>(b)) {
            if(b->getID().id == uiid.id) {
                releaseButton->onRelease();
            }
        }
    }
}

void LayoutCallbackManager::updateNode(Control *control) {
    m_clickServer.updateNode(control);
}
