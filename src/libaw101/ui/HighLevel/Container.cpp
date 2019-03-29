#include "Container.h"
#include <string>

Container::Container(AW101Layout *parent) : Control(parent) {};

CTML::Node Container::getNode() const {
    auto div = CTML::Node{"div.container#"+m_id.id};
    for(auto& child: m_children)
        div.AppendChild(child->getNode());
    return div;
}

const std::vector<std::unique_ptr<Control>> &Container::getChildren() const {
    return m_children;
}

