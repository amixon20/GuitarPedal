/*
  ==============================================================================

    Chorus.h
    Created: 30 May 2024 8:55:41am
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Chorus
{
public:
    Chorus(int sampleRate);
    ~Chorus();

    void setNumVoices(int numVoices);
    void setDelayTimes(const std::vector<float>& delayTimes);
    void setModulationDepth(float depth);
    void setModulationRate(float rate);
    void setFeedback(float feedback);

    void process(float* inputBuffer, float* outputBuffer, int bufferSize);

private:
    int m_sampleRate;
    int m_numVoices;
    float m_modulationDepth;
    float m_modulationRate;
    float m_feedback;

    std::vector<std::vector<float>> m_delayLines;
    std::vector<int> m_delayIndices;
    float m_phase;
};
