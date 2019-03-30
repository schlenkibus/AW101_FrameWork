#include "LayoutCallbackManager.h"
#include "PortBroker.h"

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

void LayoutCallbackManager::updateNode(Control *control) {
    m_clickServer.updateNode(control);
}
