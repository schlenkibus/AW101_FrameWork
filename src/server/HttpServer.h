#pragma once
#include <string>
#include <map>
#include <memory>
#include <seasocks/Server.h>
#include <seasocks/PrintfLogger.h>

template<class Handler, class ... tArgs>
class HttpServer {
public:
    HttpServer(int port, tArgs ... args);
protected:
    seasocks::Server m_server;
};

template<class Handler, class... tArgs>
HttpServer<Handler, tArgs...>::HttpServer(int port, tArgs... args)
    : m_server{std::make_shared<seasocks::PrintfLogger>()}
{
        m_server.addPageHandler(std::make_shared<Handler>(args...));
        m_server.startListening(port);
}
