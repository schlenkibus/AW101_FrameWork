#include "Label.h"

void Label::computeNode() {
    clear();
    m_node.SetName("div.Label#"+m_id.id);
    m_node.AppendText(m_text);
}

void Label::setText(const std::string& text) {
    m_text = text;
    onChange();
}

Label::Label(AW101Layout* parent, const std::string &text) : Control{parent}, m_text{text} {
}
