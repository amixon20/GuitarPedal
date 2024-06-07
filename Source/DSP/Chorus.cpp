#include <JuceHeader.h>
#include "Chorus.h"
#include <algorithm>

Chorus::Chorus(){}

Chorus::~Chorus() {}



void Chorus::process(juce::AudioBuffer<float>& buffer,
                     float fs, float depth, float rate, float delayTime, float feedback,
                     float intensity, float mix)
{
//    const int numChannels = buffer.getNumChannels();
//    const int numSamples = buffer.getNumSamples();
//    
//    int delayInSamples = (delayTime * fs);
//    maxDelayInSamples = fs * maxDelayInSeconds;
//    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineL {maxDelayInSamples};
//    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineR {maxDelayInSamples};
//    
//    float lfoPhaseL = 0.0f;
//    float lfoPhaseR = juce::MathConstants<float>::pi / 2.0f; // Phase offset for stereo LFO
//    float lfoPhaseIncrement = 2.0f * juce::MathConstants<float>::pi * rate / fs;
//    
//    for (int channel = 0; channel < numChannels; ++channel)
//    {
//        auto* data = buffer.getWritePointer(channel);
//        
//        for (int i = 0; i < numSamples; i++)
//        {
//            // Calculate LFO-modulated delay time for each channel
//            float lfoValueL = std::sin(lfoPhaseL);
//            float lfoValueR = std::sin(lfoPhaseR);
//            int modulatedDelayInSamplesL = static_cast<int>(delayInSamples + depth * lfoValueL);
//            int modulatedDelayInSamplesR = static_cast<int>(delayInSamples + depth * lfoValueR);
//            
//            // Update LFO phases
//            lfoPhaseL += lfoPhaseIncrement;
//            lfoPhaseR += lfoPhaseIncrement;
//            if (lfoPhaseL >= 2.0f * juce::MathConstants<float>::pi)
//                lfoPhaseL -= 2.0f * juce::MathConstants<float>::pi;
//            if (lfoPhaseR >= 2.0f * juce::MathConstants<float>::pi)
//                lfoPhaseR -= 2.0f * juce::MathConstants<float>::pi;
//            
//            // Push current input sample into delay lines
//            if(channel == 0) {
//                delayLineL.pushSample(channel, data[i]);
//                data[i] += delayLineL.popSample(modulatedDelayInSamplesL) * feedback;
//            }
//            else {
//                delayLineR.pushSample(channel, data[i]);
//                data[i] += delayLineR.popSample(modulatedDelayInSamplesR) * feedback;
//            }
//        }
//    }
}
