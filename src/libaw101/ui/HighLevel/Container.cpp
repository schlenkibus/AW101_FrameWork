#include "Container.h"
#include <string>

Container::Container(AW101Layout *parent) : Control(parent) {
    computeNode();
};

const std::vector<std::unique_ptr<Control>> &Container::getChildren() const {
    return m_children;
}

void Container::computeNode() {
    m_node.SetName("div.container#"+m_id.id);
    for(auto& child: m_children)
        m_node.AppendChild(child->getNode());
}

