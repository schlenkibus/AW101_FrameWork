#include "OnClickCallbackServer.h"
#include "PortBroker.h"
#include "LayoutCallbackManager.h"

class QuietLogger : public seasocks::Logger {
public:
    void log(Level level, const char *message) override {
    }
};

OnClickCallbackServer::OnClickCallbackServer(LayoutCallbackManager *manager)
    : m_manager{manager}
    , m_server{std::make_shared<QuietLogger>()}
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
    m_webSocketHandler->sendToClients(pControl->getID().id + "DATA" + pControl->getNode().ToString(CTML::StringFormatting::SINGLE_LINE));
}

seasocks::Server *OnClickCallbackServer::getServer() {
    return &m_server;
}

void ClickHandler::onData(seasocks::WebSocket *, const char *data) {
    std::string recieved{data};
    if(recieved.find("event") == 0) {
        auto commandLength = [recieved]{
            std::string numbers;
            for(auto c: recieved) {
                if(std::isdigit(c))
                    numbers += c;
                else if(!numbers.empty())
                    break;
            }
            return std::stoi(numbers);
        }();
        auto commandStr = recieved.substr(6, commandLength);
        if(commandStr == "down") {
            auto id = UIID{recieved.substr(recieved.find("UIID:"))};
            m_manager->onClickReceived(id);
        } else if(commandStr == "up") {
            auto id = UIID{recieved.substr(recieved.find("UIID:"))};
            m_manager->onReleaseReceived(id);
        } else if(commandStr == "changed") {
            auto uiidPos = recieved.find("UIID:") - 5;
            auto valuepos = recieved.find("value") - 5;
            auto idStr = recieved.substr(uiidPos + 5, valuepos - uiidPos);
            auto id = UIID{idStr};
            auto value = recieved.substr(valuepos + 10);
            m_manager->onValueChanged(id, std::stoi(value));
        }
    }
}

void ClickHandler::sendToClients(const std::string &payload) {
    m_callbackParent->getServer()->execute([this, payload](){
        for(auto c: connections)
            c->send(payload);
    });
}
