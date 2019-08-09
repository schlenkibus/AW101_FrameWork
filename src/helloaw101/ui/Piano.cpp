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
    for(auto& v: m_voicePtrs) {
      v = nullptr;
    }
}

void Piano::computeNode() {
    Container::computeNode();
    m_node.SetAttribute("class", "piano");
}

void Piano::onDown(int key) {
  for(auto& v: m_model->m_synth.m_data.m_voices) {
    if(v.m_key == key && v.m_gate)
      return;
  }
  m_model->m_synth.m_data.addNoteOn(key);
}

void Piano::onRelease(int key) {
  m_model->m_synth.m_data.removeNote(key);
}

void Piano::onKeyDown(const std::string &key) {
    try {
        std::cout << "Got Key: " << key << std::endl;
        onDown(std::stoi(key));
    } catch(...) {
    }
}

void Piano::onKeyUp(const std::string &key) {
    try {
        onRelease(std::stoi(key));
    } catch(...) {
    }
}
