#include "LayoutServer.h"
#include "LayoutHandler.h"

LayoutServer::LayoutServer(short port) : super(port, this), m_quit{false}
{
}

bool LayoutServer::isQuit() const {
    return m_quit;
}

void LayoutServer::quit() {
    m_quit = true;
}


void LayoutServer::loop() {
    m_layouts["/foo"]->loop();
}
