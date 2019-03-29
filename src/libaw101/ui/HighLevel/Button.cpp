#include <utility>
#include "../../AW101Layout.h"
#include "Button.h"

Button::Button(AW101Layout* parent, Button::tButtonCallback callback) : Control(parent), m_callback{std::move(callback)} {
    m_parent->getCallbackManager()->addButtonCallback(this);
}

void Button::onClick() {
    m_callback(this);
}

CTML::Node Button::getNode() const {
    auto buttonDiv = CTML::Node{"div.Button#"+m_id.id};
    buttonDiv.SetAttribute("onclick", "uiclick(this.id);").SetContent(m_text);
    return buttonDiv;
}
