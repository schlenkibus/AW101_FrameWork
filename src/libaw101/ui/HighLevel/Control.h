#pragma once
#include "../Intermediate/UIID.h"
#include "../../../ext/CTML/ctml.hpp"
#include "../backend/signal/Trackable.h"

class AW101Layout;

class Control : public Trackable<Control> {
public:
    explicit Control(AW101Layout* parent);
    virtual ~Control() = default;
    virtual void computeNode() = 0;
    const CTML::Node & getNode() const;
    const UIID& getID() const;
protected:
    UIID m_id;
    AW101Layout* m_parent;
    CTML::Node m_node;

    void clear();
};


