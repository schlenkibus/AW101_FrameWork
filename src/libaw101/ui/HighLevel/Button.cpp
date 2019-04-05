#include <utility>
#include "../../AW101Layout.h"
#include "Button.h"

Button::Button(AW101Layout* parent, Button::tButtonCallback callback) : Control(parent), m_downCallback{std::move(callback)} {
    m_parent->getCallbackManager()->addButtonCallback(this);
    computeNode();
}

void Button::onClick() {
    m_downCallback(this);
}

void Button::computeNode() {
    clear();
    m_node.SetName("button.Button#"+m_id.id);
    m_node.SetAttribute("onmousedown", "uiclick(this.id);");
    m_node.AppendText("Button!");
}
