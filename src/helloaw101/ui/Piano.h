#pragma once
#include "../../libaw101/ui/HighLevel/Container.h"
#include "../Synth.h"
#include "../../libaw101/ui/backend/KeyEventTarget.h"

class TestLayout;
class TestModel;

class Piano : public Container, public KeyEventTarget {
public:
    void onKeyDown(const std::string &key) override;
    void onKeyUp(const std::string &key) override;

    Piano(TestLayout* tl, TestModel* model);
    void onDown(int key);
    void onRelease(int key);

    void computeNode() override;

protected:
    std::array<Synth::Voice*, 4> m_voicePtrs;
    int m_nextVoiceIndex;
    TestModel* m_model;
};


