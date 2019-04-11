#include <utility>

#include <utility>

#include "ReleaseButton.h"

ReleaseButton::ReleaseButton(AW101Layout *parent)
    : Button(parent)
{
}

void ReleaseButton::computeNode() {
    Button::computeNode();
    m_node.SetAttribute("onmouseup", "uirelease(this.id);");
}
