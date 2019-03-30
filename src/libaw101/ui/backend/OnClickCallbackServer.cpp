#include "OnClickCallbackServer.h"
#include "PortBroker.h"
#include "LayoutCallbackManager.h"

OnClickCallbackServer::OnClickCallbackServer(LayoutCallbackManager *manager)
    : m_manager{manager}
    , m_server{std::make_shared<seasocks::PrintfLogger>()}
    , m_updateQueueControls{}
    , m_webSocketHandler(std::make_shared<ClickHandler>(manager, this))
{
    m_server.addWebSocketHandler("/click", m_webSocketHandler);
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

void OnClickCallbackServer::updateNode(Control *pControl) {
    m_webSocketHandler->sendToClients(pControl->getID().id + "_" + pControl->getNode().ToString(CTML::StringFormatting::SINGLE_LINE));
}

void ClickHandler::onData(seasocks::WebSocket *, const char *data) {
    std::string recieved{data};
    std::cout << recieved << std::endl;
    if(m_manager) {
        auto id = UIID{recieved};
        m_manager->onClickReceived(id);
    }
}

void ClickHandler::sendToClients(const std::string &payload) {
    for(auto c: connections)
        c->send(payload);
}
