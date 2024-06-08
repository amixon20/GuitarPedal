/*
  ==============================================================================

    DelayLine.cpp
    Created: 8 Jun 2024 12:17:01pm
    Author:  Alex Mixon

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayLine.h"

DelayLine::DelayLine(int maxDelay, double sampleRate)
    : delayLineLeft(maxDelay),
      delayLineRight(maxDelay),
      maxDelay(maxDelay)
{
    fs = sampleRate;
}
juce::dsp::AudioBlock<float> DelayLine::process(const juce::dsp::AudioBlock<float>& inputBlock, double delayTime)
{
    auto numSamples = inputBlock.getNumSamples();
    auto numChannels = inputBlock.getNumChannels();

    // Allocate output buffer
    juce::dsp::AudioBlock<float> outputBlock(inputBlock);

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = inputBlock.getChannelPointer(channel);
        auto* outputChannelData = outputBlock.getChannelPointer(channel);

        for (int channel = 0; channel < numChannels; ++channel)
            {
                auto* channelData = inputBlock.getChannelPointer(channel);
                auto* outputChannelData = outputBlock.getChannelPointer(channel);

                int delaySamplesLeft = static_cast<int>(delayTime * fs);
                int delaySamplesRight = static_cast<int>(delayTime * fs);
                
                for (int sample = 0; sample < numSamples; ++sample)
                        {
                            // Read delayed sample from the delay line
                            float delayedSample;
                            if (channel == 0) // Left channel
                                delayedSample = getDelayedSampleLeft(delaySamplesLeft);
                            else if (channel == 1) // Right channel
                                delayedSample = getDelayedSampleRight(delaySamplesRight);

                            // Write the delayed sample to the output block
                            outputChannelData[sample] = delayedSample;

                            // Advance the delay line
                            if (channel == 0) // Left channel
                                delayLineLeft.pushSample(channel, channelData[sample]);
                            else if (channel == 1) // Right channel
                                delayLineRight.pushSample(channel, channelData[sample]);
                        }
            }
    }

    return outputBlock;
}
float DelayLine::getDelayedSampleLeft(int delaySamples)
{
    return delayLineLeft.popSample(-delaySamples);
}

float DelayLine::getDelayedSampleRight(int delaySamples)
{
    return delayLineRight.popSample(-delaySamples);
}
