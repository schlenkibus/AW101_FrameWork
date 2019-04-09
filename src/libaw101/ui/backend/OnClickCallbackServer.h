#pragma once
#include <iostream>
#include <set>
#include <seasocks/WebSocket.h>
#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>
#include <thread>
#include "../HighLevel/Control.h"
#include <queue>

class LayoutCallbackManager;
class OnClickCallbackServer;

class ClickHandler : public seasocks::WebSocket::Handler {
public:
    ClickHandler(LayoutCallbackManager* manager, OnClickCallbackServer* srv) {
        m_manager = manager;
        m_callbackParent = srv;
    }
    LayoutCallbackManager* m_manager;
    OnClickCallbackServer* m_callbackParent;
    std::set<seasocks::WebSocket *> connections;
    void onConnect(seasocks::WebSocket *socket) override
    {
        connections.insert(socket);
    }
    void onData(seasocks::WebSocket *, const char *data) override;
    void onDisconnect(seasocks::WebSocket *socket) override
    {
        connections.erase(socket);
    }

    void sendToClients(const std::string& payload);
};

class OnClickCallbackServer
{
public:
    OnClickCallbackServer(LayoutCallbackManager* manager);
    virtual ~OnClickCallbackServer();

    void updateNode(Control *pControl);
    seasocks::Server* getServer();

    void eval(const std::string javascript);

protected:
    LayoutCallbackManager* m_manager;
    seasocks::Server m_server;
    std::thread m_bg;
    std::queue<Control*> m_updateQueueControls;
    std::shared_ptr<ClickHandler> m_webSocketHandler;
};

