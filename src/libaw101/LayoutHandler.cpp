#include "LayoutHandler.h"
#include "LayoutServer.h"

LayoutHandler::LayoutHandler(LayoutServer *parent) : m_server{parent} {

}

std::shared_ptr<seasocks::Response> LayoutHandler::handle(const seasocks::Request &request) {
    if(m_server == nullptr)
        return {};
    m_server->m_layouts[request.getRequestUri()]->getRootNode().computeNode();
    return seasocks::Response::htmlResponse(m_server->m_layouts[request.getRequestUri()]->getDocument().ToString(CTML::StringFormatting::MULTIPLE_LINES));
}