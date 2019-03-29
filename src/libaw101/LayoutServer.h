#pragma once
#include "AW101Layout.h"
#include "../server/HttpServer.h"
#include <seasocks/PageHandler.h>

class LayoutServer {
protected:
    class LayoutHandler : public seasocks::PageHandler {
    public:
        LayoutHandler(LayoutServer* parent);
        std::shared_ptr<seasocks::Response> handle(const seasocks::Request &request) override;

    private:
        LayoutServer* m_server;
    };
public:
    LayoutServer(short port);
    void addLayout(AW101Layout &&layout, std::string path);
protected:
    std::unordered_map<std::string, std::unique_ptr<AW101Layout>> m_layouts;
    HttpServer<LayoutHandler, LayoutServer*> m_server;
};


