/*
  ==============================================================================

    Chorus.cpp
    Created: 30 May 2024 8:55:41am
    Author:  Alex Mixon

  ==============================================================================
*/

#include "Chorus.h"

Chorus::Chorus(int sampleRate) :
    m_sampleRate(sampleRate),
    m_numVoices(3), // Default to 3 voices
    m_modulationDepth(0.003), // Default modulation depth of 3 milliseconds
    m_modulationRate(0.5), // Default modulation rate of 0.5 Hz
    m_feedback(0.2), // Default feedback of 20%
    m_delayLines(),
    m_delayIndices(m_numVoices, 0),
    m_phase(0.0) {
        for (int i = 0; i < m_numVoices; ++i) {
            m_delayLines.push_back(std::vector<float>(sampleRate, 0.0));
        }
    }

Chorus::~Chorus()
{
    // Destructor
}

void Chorus::setNumVoices(int numVoices) {
    m_numVoices = numVoices;
    m_delayIndices.resize(m_numVoices, 0);
    m_delayLines.clear();
    for (int i = 0; i < m_numVoices; ++i) {
        m_delayLines.push_back(std::vector<float>(m_sampleRate, 0.0));
    }
}

void Chorus::setDelayTimes(const std::vector<float>& delayTimes) {
    for (int i = 0; i < m_numVoices; ++i) {
        if (i < delayTimes.size()) {
            // Convert milliseconds to samples
            int delaySamples = static_cast<int>(delayTimes[i] * m_sampleRate / 1000.0);
            m_delayIndices[i] = (m_delayIndices[i] + delaySamples) % m_sampleRate;
        }
    }
}
void Chorus::setModulationDepth(float depth) {
    m_modulationDepth = depth;
}

void Chorus::setModulationRate(float rate) {
    m_modulationRate = rate;
}

void Chorus::setFeedback(float feedback) {
    m_feedback = feedback;
}

void Chorus::process(float* inputBuffer, float* outputBuffer, int bufferSize) {
    float phaseIncrement = 2.0 * M_PI * m_modulationRate / m_sampleRate;

    for (int i = 0; i < bufferSize; ++i) {
        for (int v = 0; v < m_numVoices; ++v) {
            // Modulate delay time using sine wave
            float delayModulation = m_modulationDepth * sin(m_phase);
            int delayIndex = (m_delayIndices[v] + static_cast<int>(delayModulation * m_sampleRate)) % m_sampleRate;
            float delayedSample = m_delayLines[v][delayIndex];

            // Apply feedback
            outputBuffer[i] = inputBuffer[i] + m_feedback * delayedSample;

            // Update delay line with new input
            m_delayLines[v][m_delayIndices[v]] = inputBuffer[i];

            // Update delay index
            m_delayIndices[v] = (m_delayIndices[v] + 1) % m_sampleRate;
        }

        // Update phase
        m_phase += phaseIncrement;
        if (m_phase >= 2.0 * M_PI) {
            m_phase -= 2.0 * M_PI;
        }
    }
}

//void Chorus::setModulationDepth(float newDepth)
//{
//    // Set the depth of the Chorus effect
//    depth = newDepth;
//    chorusProcessor.setDepth(depth);
//}
//
//void Chorus::setModulationRate(float newRate)
//{
//    // Set the rate of the Chorus effect
//    rate = newRate;
//    chorusProcessor.setRate(rate);
//}
//
//void Chorus::setFeedback(float newFeedback)
//{
//    // Set the feedback amount of the Chorus effect
//    feedback = newFeedback;
//    chorusProcessor.setFeedback(feedback);
//}
//
//void Chorus::setDelayTime(float newDelayTime)
//{
//    delayTime = newDelayTime;
//    chorusProcessor.setDelayTime(delayTime);
//}
