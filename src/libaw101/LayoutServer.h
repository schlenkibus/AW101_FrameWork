#pragma once

#include <thread>
#include "AW101Layout.h"
#include "../server/HttpServer.h"
#include "LayoutHandler.h"

class LayoutServer : HttpServer<LayoutHandler, LayoutServer*> {
public:
    typedef HttpServer<LayoutHandler, LayoutServer*> super;
    explicit LayoutServer(short port);
    template<class T>
    void addLayout(std::unique_ptr<T>& layout, const std::string& path);
    bool isQuit() const;
    void quit();
    void loop();
protected:
    bool m_quit;
    std::unordered_map<std::string, std::unique_ptr<AW101Layout>> m_layouts;
    friend class LayoutHandler;
};


template<class T>
void LayoutServer::addLayout(std::unique_ptr<T>& layout, const std::string &path) {
    m_layouts[path] = std::move(layout);
}

