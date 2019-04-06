#pragma once
#include "../../libaw101/ui/HighLevel/Container.h"
#include "../Synth.h"

class TestLayout;
class TestModel;

class Piano : public Container {
public:
    Piano(TestLayout* tl, TestModel* model);
    void onDown(int key);
    void onRelease(int key);

    void computeNode() override;

protected:
    std::array<Synth::Voice*, 4> m_voicePtrs;
    int m_nextVoiceIndex;
    TestModel* m_model;
};


