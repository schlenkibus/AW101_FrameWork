#include "Piano.h"
#include "../TestLayout.h"
#include "../../libaw101/ui/HighLevel/ReleaseButton.h"

Piano::Piano(TestLayout *tl, TestModel *model)
    : Container(tl)
    , m_model{model}
    , m_nextVoiceIndex{0}
{
    for(auto i = 0; i < 16; i++)
        m_children.emplace_back(std::make_unique<ReleaseButton>(tl, [this, &model, i](Button* b) {
            onDown(i);
        }, [this, i](Button* b) {
            onRelease(i);
        }));
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
