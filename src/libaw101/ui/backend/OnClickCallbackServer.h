#pragma once
#include <iostream>
#include <set>
#include <seasocks/WebSocket.h>
#include <seasocks/PrintfLogger.h>
#include <seasocks/Server.h>
#include <thread>

class LayoutCallbackManager;

struct ClickHandler : seasocks::WebSocket::Handler {
    std::set<seasocks::WebSocket *> connections;
    void onConnect(seasocks::WebSocket *socket) override
    {
        connections.insert(socket);
    }
    void onData(seasocks::WebSocket *, const char *data) override
    {
        for (auto c : connections) c->send(data);
    }
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

