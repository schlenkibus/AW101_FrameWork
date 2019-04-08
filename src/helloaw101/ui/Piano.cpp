#include "Piano.h"
#include "../TestLayout.h"
#include "../../libaw101/ui/HighLevel/ReleaseButton.h"
#include "../../libaw101/ui/HighLevel/Label.h"

Piano::Piano(TestLayout *tl, TestModel *model)
    : Container(tl)
    , m_model{model}
    , m_nextVoiceIndex{0}
{
    m_parent->getCallbackManager()->addKeyEventTarget(this);
    addChild<Label>(tl, "Hello Piano<br> Controls:<br> keys 0 - 9 start a voice with respective semitone");
}

void Piano::computeNode() {
    Container::computeNode();
    m_node.SetAttribute("class", "piano");
}

void Piano::onDown(int key) {
    m_voicePtrs[m_nextVoiceIndex] = m_model->m_synth.m_data.addNoteOn(key);
    if(m_nextVoiceIndex >= m_voicePtrs.size())
        m_nextVoiceIndex = 0;
}

void Piano::onRelease(int key) {
    m_model->m_synth.m_data.removeNote(key);
}

void Piano::onKeyDown(const std::string &key) {
    std::cerr << key << std::endl;
    try {
        onDown(std::stoi(key));
    } catch(...) {
        std::cerr << key << " not a valid number" << std::endl;
    }
}

void Piano::onKeyUp(const std::string &key) {
    try {
        onRelease(std::stoi(key));
    } catch(...) {
        std::cerr << key << " not a valid number" << std::endl;
    }
}
