#pragma once

#include "ui/HighLevel/Container.h"
#include "ui/backend/LayoutCallbackManager.h"

class AW101Layout : public Trackable<AW101Layout> {
public:
    AW101Layout();
    LayoutCallbackManager* getCallbackManager();
    CTML::Document getDocument() const;
    Container& getRootNode();
protected:
    Container m_root;
    LayoutCallbackManager m_callbackManager;
};


