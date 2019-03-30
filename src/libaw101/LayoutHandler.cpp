#include "LayoutHandler.h"
#include "LayoutServer.h"

LayoutHandler::LayoutHandler(LayoutServer *parent) : m_server{parent} {

}

std::shared_ptr<seasocks::Response> LayoutHandler::handle(const seasocks::Request &request) {
    if(m_server == nullptr)
        return {};
    std::cout << request.getRequestUri() << std::endl;
    std::cout << m_server->m_layouts.size() << std::endl;
    m_server->m_layouts["/foo"]->getRootNode().computeNode();
    return seasocks::Response::htmlResponse(m_server->m_layouts["/foo"]->getDocument().ToString(CTML::StringFormatting::MULTIPLE_LINES));
}