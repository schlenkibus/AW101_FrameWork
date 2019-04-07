#include "LayoutCallbackManager.h"
#include "PortBroker.h"
#include "../HighLevel/ReleaseButton.h"
#include "../HighLevel/Slider.h"

LayoutCallbackManager::LayoutCallbackManager() : m_clickServer{this} {

}

void LayoutCallbackManager::addButtonCallback(Button *button) {
    m_buttons.emplace_back(button);
}

void LayoutCallbackManager::addSlider(Slider *slider) {
    m_sliders.emplace_back(slider);
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

void LayoutCallbackManager::onValueChanged(const UIID &id, int value) {
    for(auto& s: m_sliders) {
        if(s->getID().id == id.id) {
            s->onValueChanged(value);
            break;
        }
    }
}

void LayoutCallbackManager::onKeyDown(std::string key) {
    for(auto& target: m_keyEventTargets) {
        target->onKeyDown(key);
    }
}

void LayoutCallbackManager::onKeyUp(std::string key) {
    for(auto& target: m_keyEventTargets) {
        target->onKeyUp(key);
    }
}

void LayoutCallbackManager::addKeyEventTarget(KeyEventTarget* target) {
    m_keyEventTargets.emplace_back(target);
}
