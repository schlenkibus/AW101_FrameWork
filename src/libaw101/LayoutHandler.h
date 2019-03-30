#pragma once
#include <seasocks/PageHandler.h>

class LayoutServer;

class LayoutHandler : public seasocks::PageHandler {
public:
    LayoutHandler(LayoutServer* parent);
    std::shared_ptr<seasocks::Response> handle(const seasocks::Request &request) override;
private:
    LayoutServer* m_server;
};