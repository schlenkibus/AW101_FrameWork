#pragma once
#include "../Intermediate/UIID.h"
#include "../CTML/ctml.hpp"
#include "../backend/signal/Trackable.h"

class AW101Layout;

class Control : public Trackable<Control> {
public:
    explicit Control(AW101Layout* parent);
    virtual CTML::Node getNode() const = 0;
    void setText(const std::string& string);
    const UIID& getID() const;
protected:
    UIID m_id;
    std::string m_text;
    AW101Layout* m_parent;
};


