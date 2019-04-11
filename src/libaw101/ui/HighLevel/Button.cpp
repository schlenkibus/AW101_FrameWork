#include <utility>
#include "../../AW101Layout.h"
#include "Button.h"

Button::Button(AW101Layout* parent)
    : Control(parent)
    , m_buttonText{m_id.id}
{
    m_parent->getCallbackManager()->addButtonCallback(this);
    computeNode();
}

void Button::computeNode() {
    clear();
    m_node.SetName("button.Button#"+m_id.id);
    m_node.SetAttribute("onmousedown", "uiclick(this.id);");
    m_node.AppendText(getButtonText());
}

const std::string &Button::getButtonText() const {
    return m_buttonText;
}
