#include "CollapseableContainer.h"

CollapseableContainer::CollapseableContainer(AW101Layout *parent) : Container(parent) {
    m_toggleButton = addChild<ToggleButton>(parent);
}

void CollapseableContainer::computeNode() {
    Container::computeNode();
    m_node.SetAttribute("display", m_toggleButton->isOpen() ? "block" : "none");
}

//Toggle Button

CollapseableContainer::ToggleButton::ToggleButton(AW101Layout *parent) : Button(parent) {
    m_buttonText = "Toggle";
}

void CollapseableContainer::ToggleButton::onClick() {
    m_open = !m_open;
    onChange();
}

bool CollapseableContainer::ToggleButton::isOpen() const {
    return m_open;
}
