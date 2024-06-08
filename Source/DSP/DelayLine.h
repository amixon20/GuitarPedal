/*
  ==============================================================================

    DelayLine.h
    Created: 8 Jun 2024 12:17:01pm
    Author:  Alex Mixon

  ==============================================================================
*/

#pragma once
class DelayLine
{
public:
    
    DelayLine(int maxDelay, double sampleRate);
    
    juce::dsp::AudioBlock<float> process(const juce::dsp::AudioBlock<float>& inputBlock, double delayTime);
    
    int getSampleRate() { return fs; };
    
private:
    
    int fs;
    
    float getDelayedSampleLeft(int delaySamples);
    
    float getDelayedSampleRight(int delaySamples);
    
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineLeft;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineRight;
    int maxDelay;
};
