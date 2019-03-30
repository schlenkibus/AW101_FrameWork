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
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}
