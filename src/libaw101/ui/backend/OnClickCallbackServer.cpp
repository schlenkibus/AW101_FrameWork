#include "OnClickCallbackServer.h"
#include "PortBroker.h"

OnClickCallbackServer::OnClickCallbackServer(LayoutCallbackManager *manager)
    : m_manager{manager}
    , m_server{std::make_shared<seasocks::PrintfLogger>()}
{
    m_server.addWebSocketHandler("/click", std::make_shared<ClickHandler>());
    m_bg = std::thread{[this]{
        m_server.serve("web", PortBroker::getOnClickPort());
    }};
}

OnClickCallbackServer::~OnClickCallbackServer() {
    m_server.terminate();
    if(m_bg.joinable())
        m_bg.join();
    else
        std::cerr << "CallBackServer not Responding!\n";
}
