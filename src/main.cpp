// Server
// Serves UI Layouts by Instantiating States
// State:
// UI Layout
// Cpp Objects that correspond to HTML Website
// Callbacks from Web via WebSockets (but hidden from user)
// Model:
// Can be any pod
// Background Actions:
// Can be anything, gets run at high prio
// ex, dsp or data streaming

#include <iostream>
#include "libaw101/LayoutServer.h"
#include "helloaw101/TestModel.h"
#include "helloaw101/TestLayout.h"
#include <memory>

int main(int argc, char** argv) {
    TestModel model;
    LayoutServer server{80};
    auto testLayout = std::make_unique<TestLayout>{&model};
    server.addLayout(std::move(testLayout), "/");
    server.serve();
    return ;
}