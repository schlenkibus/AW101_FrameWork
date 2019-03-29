#include "Control.h"

Control::Control(AW101Layout *parent) : m_parent{parent} {

}

void Control::setText(const std::string &string) {
    m_text = string;
    onChange();
}

const UIID &Control::getID() const {
    return m_id;
}
