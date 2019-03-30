#include "Label.h"
#include "../../AW101Layout.h"

void Label::computeNode() {
    clear();
    m_node.SetName("div.Label#"+m_id.id);
    m_node.AppendText(m_text);
}

void Label::setText(const std::string& text) {
    m_text = text;
    onChange();
}

const std::string& Label::getText() const {
    return m_text;
}


Label::Label(AW101Layout* parent, const std::string &text) : Control{parent}, m_text{text} {
    registerCallback([this](auto* label) {
        m_parent->getCallbackManager()->updateNode(label);
    });
}
