#include "CSSBoilerplate.h"

CSSBoilerplate::CSSBoilerplate() : m_node{"style"} {
    m_node.AppendText(
            ".width-half { width: 50%; }"\
            ".width-full { width: 50%; }"\
            ".Button { pointer: cursor; }"\
            ".Button:hover { background-color: gray; }"
            );
}

const CTML::Node &CSSBoilerplate::getNode() {
    return m_node;
}
