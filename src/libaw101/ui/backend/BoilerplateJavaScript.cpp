#include "BoilerplateJavaScript.h"
#include "PortBroker.h"

const std::string BoilerplateJavaScript::getScriptContent() const {
    return  "var onClickWS = new WebSocket('ws://localhost:" + std::to_string(PortBroker::getOnClickPort()) + "/click');"\
            "onClickWS.onmessage = function(event) {"\
            "console.log(event);"\
            "var text = event.data;"\
            "if(text.startsWith('EVAL:')) {"\
                "var js = text.substring(5);"\
                "eval(js);"\
            "}"\
            "else {"\
                "var dataentry = text.indexOf('DATA');"\
                "var id = text.substring(0,dataentry);"\
                "var payload = text.substring(dataentry+4);"\
                "updateNode(id, payload);"
            "}"\
            "};"\
            "var body;"
            "async function onLoad() {"\
            "await Sleep(100);"\
            "body = document.body;"\
            "body.onkeydown = function(e) {"\
            "keydown(onKeyEvent(e));"\
            "};"\
            "body.onkeyup = function(e) {"\
            "keyup(onKeyEvent(e));"\
            "};"\
            "}"\
            "function onKeyEvent(event) {"\
            "return event.key;"\
            "}"\
            "function uiclick(id) {"\
            "onClickWS.send('event4down'+id);"\
            "}"\
            "function uirelease(id) {"\
            "onClickWS.send('event2up'+id);"\
            "}"\
            "function keyup(key) {"\
            "onClickWS.send('event5keyup'+key)"\
            "}"\
            "function keydown(key) {"\
            "onClickWS.send('event7keydown'+key)"\
            "}"\
            "function valuechange(id,value) {"\
            "onClickWS.send('event7changed'+id+'value'+value)"\
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
            "}"\
            "function Sleep(milliseconds) {"\
            " return new Promise(resolve => setTimeout(resolve, milliseconds));"\
            "}"\
            "Sleep(100);"\
            "onLoad();";
}
