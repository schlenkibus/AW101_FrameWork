#include "AW101Layout.h"
#include "ui/backend/LayoutCallbackManager.h"

AW101Layout::AW101Layout() : m_callbackManager{}, m_root{this} {

}

LayoutCallbackManager *AW101Layout::getCallbackManager() {
    return &m_callbackManager;
}
