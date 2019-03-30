#pragma once
#include <string>
#include <map>
#include <memory>
#include <seasocks/Server.h>
#include <seasocks/PrintfLogger.h>
#include <thread>

template <class tHandler, class ... tArgs>
class HttpServer {
public:
    HttpServer(int port, tArgs ... args);
    virtual ~HttpServer();

protected:
    seasocks::Server m_server;
    std::shared_ptr<tHandler> m_handler;
    std::thread m_bg;
};

template<class tHandler, class ... tArgs>
HttpServer<tHandler, tArgs...>::HttpServer(int port, tArgs ... args)
    : m_server{std::make_shared<seasocks::PrintfLogger>()},
      m_handler{std::make_shared<tHandler>(args...)}
{
    m_server.addPageHandler(m_handler);
    m_server.startListening(port);
    m_bg = std::thread{[this](){
        while(m_server.poll(10) == seasocks::Server::PollResult::Continue);
        std::cout << "Server not looping anymore!\n";
    }};
}

template<class tHandler, class... tArgs>
HttpServer<tHandler, tArgs...>::~HttpServer() {
    m_server.terminate();
    if(m_bg.joinable())
        m_bg.join();
    else
        std::cerr << "HttpServer not Responding!\n";
}
