#include "BoilerplateJavaScript.h"
#include "PortBroker.h"

const std::string BoilerplateJavaScript::getScriptContent() const {
    return  "var onClickWS = new WebSocket('ws://localhost:" + std::to_string(PortBroker::getOnClickPort()) + "/click');"\
            "onClickWS.onmessage = function(event) {"\
            "console.log(event);"\
            "var text = event.data;"\
            "var id = text.substring(0,6);"\
            "var payload = text.substring(7);"\
            "updateNode(id, payload);"
            "};"\
            "function uiclick(id) {"\
            "onClickWS.send('event4down'+id);"\
            "}"\
            "function uirelease(id) {"\
            "onClickWS.send('event2up'+id);"\
            "}"\
            "function htmlToElement(html) {"\
            "var template = document.createElement('template');"\
            "html = html.trim();"\
            "template.innerHTML = html;"\
            "return template.content.firstChild;"\
            "}"\
            "function updateNode(id, content) {"\
            "var toChange = document.getElementById(id);"\
            "var parent = toChange.parentElement;"\
            "parent.replaceChild(htmlToElement(content), toChange);"\
            "}";
}
