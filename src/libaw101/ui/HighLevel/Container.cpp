#include "Container.h"
#include "Control.h"

Container::Container(AW101Layout *parent) : Control(parent) {
    computeNode();
};

std::vector<std::unique_ptr<Control>> & Container::getChildren() {
    return m_children;
}

void Container::computeNode() {
    clear();
    m_node.SetName("div.container#"+m_id.id);
    for(auto& child: m_children)
    {
        child->computeNode();
        m_node.AppendChild(child->getNode());
    }
}

