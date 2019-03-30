#pragma once
#include <iostream>
#include <set>
#include <seasocks/WebSocket.h>
#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>
#include <thread>

class LayoutCallbackManager;

class ClickHandler : public seasocks::WebSocket::Handler {
public:
    ClickHandler(LayoutCallbackManager* manager) {
        m_manager = manager;
    }
    LayoutCallbackManager* m_manager;
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
};

class OnClickCallbackServer
{
public:
    OnClickCallbackServer(LayoutCallbackManager* manager);
    virtual ~OnClickCallbackServer();
protected:
    LayoutCallbackManager* m_manager;
    seasocks::Server m_server;
    std::thread m_bg;
};

