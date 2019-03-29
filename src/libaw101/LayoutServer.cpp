#include "LayoutServer.h"

LayoutServer::LayoutServer(short port) : m_server{port, this} {
}

void LayoutServer::addLayout(AW101Layout &&layout, std::string path) {
    m_layouts[path] = std::make_unique<AW101Layout>(layout);
}

LayoutServer::LayoutHandler::LayoutHandler(LayoutServer *parent) : m_server{parent} {

}

std::shared_ptr<seasocks::Response> LayoutServer::LayoutHandler::handle(const seasocks::Request &request) {
    std::cout << request.getRequestUri() << std::endl;
    std::cout << m_server->m_layouts.size() << std::endl;
    return std::shared_ptr<seasocks::Response>();
}
