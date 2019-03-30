#include "BoilerplateJavaScript.h"
#include "PortBroker.h"

const std::string BoilerplateJavaScript::getScriptContent() const {
    return  "var onClickWS = new WebSocket('ws://localhost:" + std::to_string(PortBroker::getOnClickPort()) + "/click');"\
            "function uiclick(id) {"\
            "onClickWS.send(id);"\
            "}";
}
