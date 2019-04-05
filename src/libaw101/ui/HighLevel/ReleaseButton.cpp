#include <utility>

#include <utility>

#include "ReleaseButton.h"

ReleaseButton::ReleaseButton(AW101Layout *parent, Button::tButtonCallback downCB, Button::tButtonCallback upCB)
    : Button(parent, std::move(downCB))
    , m_reaseCallback{std::move(upCB)}
{

}

void ReleaseButton::onRelease() {
    m_reaseCallback(this);
}

void ReleaseButton::computeNode() {
    Button::computeNode();
    m_node.SetAttribute("onmouseup", "uirelease(this.id);");
}
