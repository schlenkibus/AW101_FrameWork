#include "Control.h"

Control::Control(AW101Layout *parent) : m_parent{parent} {
    registerCallback([](Control* c) {
        c->computeNode();
    });
}

const UIID &Control::getID() const {
    return m_id;
}

const CTML::Node &Control::getNode() const {
    return m_node;
}
