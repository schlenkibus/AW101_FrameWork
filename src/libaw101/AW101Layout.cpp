#include "AW101Layout.h"
#include "ui/backend/LayoutCallbackManager.h"
#include "ui/backend/BoilerplateJavaScript.h"

AW101Layout::AW101Layout() : m_callbackManager{}, m_root{this} {
}

LayoutCallbackManager *AW101Layout::getCallbackManager() {
    return &m_callbackManager;
}

CTML::Document AW101Layout::getDocument() const {
    CTML::Document ret;
    BoilerplateJavaScript js;
    ret.head().AppendChild(js.getNode());
    ret.body().AppendChild(m_root.getNode());
    return ret;
}
