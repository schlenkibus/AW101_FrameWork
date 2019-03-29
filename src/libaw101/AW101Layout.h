#pragma once

#include "ui/HighLevel/Container.h"
#include "ui/backend/LayoutCallbackManager.h"

class AW101Layout {
public:
    AW101Layout();
    LayoutCallbackManager* getCallbackManager();
protected:
    Container m_root;
    LayoutCallbackManager m_callbackManager;
};


