#include "JavaScript.h"

JavaScript::JavaScript() = default;

const CTML::Node& JavaScript::getNode() const {
    return m_node;
}

void JavaScript::computeNode() {
    m_node.SetName("script");
    m_node.AppendText(getScriptContent());
}
