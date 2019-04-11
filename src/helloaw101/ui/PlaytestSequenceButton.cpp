#include "PlaytestSequenceButton.h"

PlaytestSequenceButton::PlaytestSequenceButton(AW101Layout *parent, TestModel *model) : Button(parent), m_model{model}
{
    m_buttonText = "Play Sequence!";
}

void PlaytestSequenceButton::onClick() {
    m_model->m_synth.playSequence();
}
