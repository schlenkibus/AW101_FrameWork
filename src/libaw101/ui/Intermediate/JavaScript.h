#pragma once
#include "../../../ext/CTML/ctml.hpp"

class JavaScript {
public:
    JavaScript();
    virtual void computeNode();
    const CTML::Node& getNode() const;
    virtual const std::string getScriptContent() const = 0;
protected:
    CTML::Node m_node;
};


