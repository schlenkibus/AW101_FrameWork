#pragma once
#include "../../../ext/CTML/ctml.hpp"

class CSSBoilerplate {
public:
    CSSBoilerplate();
    const CTML::Node& getNode();
protected:
    CTML::Node m_node;
};


